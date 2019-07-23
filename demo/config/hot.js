/* eslint-disable */
export {};

const ReactFreshRuntime = require('./react-fresh/runtime');

let currentModuleID = null;
window.__setCurrentModule__ = function(m) {
  currentModuleID = m.id;
};

let scheduleHotUpdate;
let findHostNodesForHotUpdate;
let roots = new Set();
let knownTypes = new WeakSet();
let idsByFile = new Map();

if (!window.__REACT_DEVTOOLS_GLOBAL_HOOK__) {
  window.__REACT_DEVTOOLS_GLOBAL_HOOK__ = {
    supportsFiber: true,
    inject() {},
    onCommitFiberRoot: () => {},
    onCommitFiberUnmount: () => {},
  };
}
function patchHook(method, intercept) {
  let oldFn = window.__REACT_DEVTOOLS_GLOBAL_HOOK__[method];
  window.__REACT_DEVTOOLS_GLOBAL_HOOK__[method] = (...args) => {
    intercept(...args);
    return oldFn(...args);
  };
}
patchHook('inject', injected => {
  scheduleHotUpdate = injected.scheduleHotUpdate;
  findHostNodesForHotUpdate = injected.findHostNodesForHotUpdate;
});
patchHook('onCommitFiberRoot', (id, root) => {
  // TODO: properly track roots
  roots.add(root);
});

const REACT_PROVIDER_TYPE = Symbol.for('react.provider');
const REACT_CONTEXT_TYPE = Symbol.for('react.context');
const REACT_FORWARD_REF_TYPE = Symbol.for('react.forward_ref');
const REACT_MEMO_TYPE = Symbol.for('react.memo');

window.__shouldAccept__ = function(exports) {
  __register__(exports, '%%exports%%');

  for (let key in exports) {
    const val = exports[key];
    __register__(val, '%%exports%%' + key);
    if (!val) {
      return false;
    }
    if (typeof val === 'string') {
      return false;
    }
    if (typeof val === 'object') {
      switch (val.$$typeof) {
        case REACT_MEMO_TYPE:
        case REACT_FORWARD_REF_TYPE:
          continue;
        // case REACT_PROVIDER_TYPE:
        // case REACT_CONTEXT_TYPE:
        //   return false;
        default:
          return false;
      }
    }
    if (typeof val === 'function') {
      if (val.prototype) {
        if (val.prototype.isReactComponent) {
          return true;
        }
        for (let inner in val.prototype) {
          return false;
        }
      }
    }
    if (knownTypes.has(val)) {
      continue;
    }
    return false;
  }
  // All exports are component-ish.
  return true;
};

function __register__(type, id) {
  if (
    (typeof type !== 'function' && typeof type !== 'object') ||
    type == null
  ) {
    return;
  }
  knownTypes.add(type);
  const fullID = currentModuleID + '%' + id;

  let ids = idsByFile.get(currentModuleID);
  if (!ids) {
    idsByFile.set(currentModuleID, new Set());
  }
  idsByFile.get(currentModuleID).add(fullID);

  ReactFreshRuntime.register(type, fullID);
  scheduleHotReload();
}
window.__register__ = __register__;

function __signature__() {
  let call = 0;
  let savedType;
  let hasCustomHooks;
  return function(type, key, forceReset, getCustomHooks) {
    switch (call++) {
      case 0:
        savedType = type;
        hasCustomHooks = typeof getCustomHooks === 'function';
        ReactFreshRuntime.setSignature(type, key, forceReset, getCustomHooks);
        break;
      case 1:
        if (hasCustomHooks) {
          ReactFreshRuntime.collectCustomHooksForSignature(savedType);
        }
        break;
    }
    return type;
  };
}
window.__signature__ = __signature__;

window.__onEdit__ = function(file) {
  const ids = idsByFile.get(file);
  if (!ids) {
    return;
  }
  let families = new Set();
  ids.forEach(id => {
    const family = ReactFreshRuntime.getFamilyByID(id);
    if (family) {
      families.add(family);
    }
  });

  let nodes = new Set();
  roots.forEach(root => {
    findHostNodesForHotUpdate(root, Array.from(families)).forEach(node => {
      nodes.add(node);
    });
  });
  clearTimeout(stuckHandle);
  highlightNodes(Array.from(nodes));
  stuckHandle = setTimeout(() => {
    highlightNodes([]);
  }, 3000);
};

let stuckHandle;

let waitHandle = null;
function scheduleHotReload() {
  clearTimeout(stuckHandle);
  if (!waitHandle) {
    waitHandle = setTimeout(() => {
      waitHandle = null;

      const update = ReactFreshRuntime.prepareUpdate();
      if (update === null) {
        return;
      }
      highlightNodes([]);
      roots.forEach(root => scheduleHotUpdate(root, update));
      // TODO
    }, 30);
  }
}

function highlightNodes(nodes) {
  let rects = nodes.map(node => node.getBoundingClientRect());
  let layer = ensureLayer();

  layer.innerHTML = '';
  for (let i = 0; i < rects.length; i++) {
    const rect = rects[i];
    const div = document.createElement('div');
    Object.assign(div.style, rectStyles, {
      left: rect.left + 'px',
      top: rect.top + 'px',
      width: rect.width + 'px',
      height: rect.height + 'px',
    });
    layer.appendChild(div);
  }
}

const layerStyles = {
  position: 'fixed',
  top: '0',
  left: '0',
  width: '100%',
  height: '100%',
  border: 'none',
  pointerEvents: 'none',
  zIndex: 2147483647,
};

const rectStyles = {
  position: 'absolute',
  backgroundColor: 'rgba(0, 0, 0, 0.1)',
};

let l;
function ensureLayer() {
  if (l) {
    return l;
  }
  // TODO: iframe
  l = document.createElement('div');
  Object.assign(l.style, layerStyles);
  document.body.appendChild(l);
  return l;
}
