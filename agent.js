function hook(options) {
    var realFuncPtr = Module.getExportByName(options.module, options.func);
    Interceptor.replace(realFuncPtr, new NativeCallback(function () {
        var args = Array.prototype.slice.call(arguments);
        return options.replace(args);
    }, options.retType, options.argsType));
}

function getRealFunc(options) {
    var funcPtr = Module.getExportByName(options.module, options.func);
    return new NativeFunction(funcPtr, options.retType, options.argsType);
}

var real_open = getRealFunc({
    module: null,
    func: 'open',
    retType: 'int',
    argsType: ['pointer', 'int', 'int'],
});

var real_reamove = getRealFunc({
    module: null,
    func: 'remove',
    retType: 'int',
    argsType: ['pointer'],
});

hook({
    module: null,
    func: 'open',
    retType: 'int',
    argsType: ['pointer', 'int', 'int'],
    replace: function (args) {
        var path = args[0].readUtf8String();
        var flags = args[1];
        var mode = args[2];
        if (path.endsWith('/.DS_Store')) {
            console.log('!!! open(path=' + path + ', flags=' + flags + ', mode=' + mode + ')');
            var ret = real_reamove(args[0]);
            console.log('!!! remove(path=' + path + ') = ' + ret);
            return -1;
        }
        var ret = real_open.apply(null, args);
        return ret;
    }
});

