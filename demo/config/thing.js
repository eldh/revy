module.exports = transform;

function transform(babel) {
  let t = babel.types;

  let buildSetCurrentModule = babel.template(`
    if (typeof __setCurrentModule__ !== 'undefined') {
      __setCurrentModule__(module)
    }
  `);

  let buildModuleHotAcceptCall = babel.template(`
    function __hotErrorHandler__(err) {
      require.cache[module.id].hot.accept(__hotErrorHandler__);
    }
    if (typeof __shouldAccept__ === 'function' && __shouldAccept__(module.__proto__.exports)) {
      module.hot.accept(__hotErrorHandler__);
    }
  `);

  return {
    visitor: {
      Program: {
        exit(path) {
          const isBuiltIn =
            path.hub.file.opts.filename &&
            path.hub.file.opts.filename.indexOf('/webpack/') > -1;

          if (!isBuiltIn) {
            path.unshiftContainer('body', buildSetCurrentModule());
          }
          path.pushContainer('body', buildModuleHotAcceptCall());
        },
      },
    },
  };
}
