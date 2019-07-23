/** @license React vundefined
 * react-fresh-runtime.development.js
 *
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

'use strict';

if (process.env.NODE_ENV !== 'production') {
  (function() {
    'use strict';

    // The Symbol used to tag the ReactElement-like types. If there is no native Symbol
    // nor polyfill, then a plain number is used for performance.
    var hasSymbol = typeof Symbol === 'function' && Symbol.for;

    // TODO: We don't use AsyncMode or ConcurrentMode anymore. They were temporary
    // (unstable) APIs that have been removed. Can we remove the symbols?

    var REACT_FORWARD_REF_TYPE = hasSymbol
      ? Symbol.for('react.forward_ref')
      : 0xead0;

    var REACT_MEMO_TYPE = hasSymbol ? Symbol.for('react.memo') : 0xead3;

    // React event targets

    // We never remove these associations.
    // It's OK to reference families, but use WeakMap/Set for types.
    var allFamiliesByID = new Map();
    var allTypes = new WeakSet();
    var allSignaturesByType = new WeakMap();
    // This WeakMap is read by React, so we only put families
    // that have actually been edited here. This keeps checks fast.
    var familiesByType = new WeakMap();

    // This is cleared on every prepareUpdate() call.
    // It is an array of [Family, NextType] tuples.
    var pendingUpdates = [];

    function computeFullKey(signature) {
      if (signature.fullKey !== null) {
        return signature.fullKey;
      }

      var fullKey = signature.ownKey;
      var hooks = void 0;
      try {
        hooks = signature.getCustomHooks();
      } catch (err) {
        // This can happen in an edge case, e.g. if expression like Foo.useSomething
        // depends on Foo which is lazily initialized during rendering.
        // In that case just assume we'll have to remount.
        signature.forceReset = true;
        signature.fullKey = fullKey;
        return fullKey;
      }

      for (var i = 0; i < hooks.length; i++) {
        var hook = hooks[i];
        if (typeof hook !== 'function') {
          // Something's wrong. Assume we need to remount.
          signature.forceReset = true;
          signature.fullKey = fullKey;
          return fullKey;
        }
        var nestedHookSignature = allSignaturesByType.get(hook);
        if (nestedHookSignature === undefined) {
          // No signature means Hook wasn't in the source code, e.g. in a library.
          // We'll skip it because we can assume it won't change during this session.
          continue;
        }
        var nestedHookKey = computeFullKey(nestedHookSignature);
        if (nestedHookSignature.forceReset) {
          signature.forceReset = true;
        }
        fullKey += '\n---\n' + nestedHookKey;
      }

      signature.fullKey = fullKey;
      return fullKey;
    }

    function haveEqualSignatures(prevType, nextType) {
      var prevSignature = allSignaturesByType.get(prevType);
      var nextSignature = allSignaturesByType.get(nextType);

      if (prevSignature === undefined && nextSignature === undefined) {
        return true;
      }
      if (prevSignature === undefined || nextSignature === undefined) {
        return false;
      }
      if (computeFullKey(prevSignature) !== computeFullKey(nextSignature)) {
        return false;
      }
      if (nextSignature.forceReset) {
        return false;
      }

      return true;
    }

    function isReactClass(type) {
      return type.prototype && type.prototype.isReactComponent;
    }

    function canPreserveStateBetween(prevType, nextType) {
      if (isReactClass(prevType) || isReactClass(nextType)) {
        return false;
      }
      if (haveEqualSignatures(prevType, nextType)) {
        return true;
      }
      return false;
    }

    function resolveFamily(type) {
      return familiesByType.get(type);
    }

    function prepareUpdate() {
      if (pendingUpdates.length === 0) {
        return null;
      }

      var staleFamilies = new Set();
      var updatedFamilies = new Set();

      var updates = pendingUpdates;
      pendingUpdates = [];
      updates.forEach(function(_ref) {
        var family = _ref[0],
          nextType = _ref[1];

        // Now that we got a real edit, we can create associations
        // that will be read by the React reconciler.
        var prevType = family.current;
        familiesByType.set(prevType, family);
        familiesByType.set(nextType, family);
        family.current = nextType;

        // Determine whether this should be a re-render or a re-mount.
        if (canPreserveStateBetween(prevType, nextType)) {
          updatedFamilies.add(family);
        } else {
          staleFamilies.add(family);
        }
      });

      return {
        resolveFamily: resolveFamily,
        updatedFamilies: updatedFamilies,
        staleFamilies: staleFamilies,
      };
    }

    function register(type, id) {
      if (type === null) {
        return;
      }
      if (typeof type !== 'function' && typeof type !== 'object') {
        return;
      }

      // This can happen in an edge case, e.g. if we register
      // return value of a HOC but it returns a cached component.
      // Ignore anything but the first registration for each type.
      if (allTypes.has(type)) {
        return;
      }
      allTypes.add(type);

      // Create family or remember to update it.
      // None of this bookkeeping affects reconciliation
      // until the first prepareUpdate() call above.
      var family = allFamiliesByID.get(id);
      if (family === undefined) {
        family = { current: type };
        allFamiliesByID.set(id, family);
      } else {
        pendingUpdates.push([family, type]);
      }

      // Visit inner types because we might not have registered them.
      if (typeof type === 'object' && type !== null) {
        switch (type.$$typeof) {
          case REACT_FORWARD_REF_TYPE:
            register(type.render, id + '$render');
            break;
          case REACT_MEMO_TYPE:
            register(type.type, id + '$type');
            break;
        }
      }
    }

    function setSignature(type, key) {
      var forceReset =
        arguments.length > 2 && arguments[2] !== undefined
          ? arguments[2]
          : false;
      var getCustomHooks = arguments[3];

      allSignaturesByType.set(type, {
        forceReset: forceReset,
        ownKey: key,
        fullKey: null,
        getCustomHooks:
          getCustomHooks ||
          function() {
            return [];
          },
      });
    }

    // This is lazily called during first render for a type.
    // It captures Hook list at that time so inline requires don't break comparisons.
    function collectCustomHooksForSignature(type) {
      var signature = allSignaturesByType.get(type);
      if (signature !== undefined) {
        computeFullKey(signature);
      }
    }

    function getFamilyByID(id) {
      return allFamiliesByID.get(id);
    }

    var ReactFreshRuntime = Object.freeze({
      prepareUpdate: prepareUpdate,
      register: register,
      setSignature: setSignature,
      collectCustomHooksForSignature: collectCustomHooksForSignature,
      getFamilyByID: getFamilyByID,
    });

    // This is hacky but makes it work with both Rollup and Jest.
    var runtime = ReactFreshRuntime.default || ReactFreshRuntime;

    module.exports = runtime;
  })();
}
