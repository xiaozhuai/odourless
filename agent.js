console.log('hello from agent!');

var cagePath = '/usr/local/var/.odourless_cage';

function replaceFunc(options) {
    var realFuncPtr = Module.getExportByName(options.module, options.func);
    var realFunc = new NativeFunction(realFuncPtr, options.retType, options.argsType);
    Interceptor.replace(realFuncPtr, new NativeCallback(function () {
        var args = Array.prototype.slice.call(arguments);
        return options.replace(args, realFunc);
    }, options.retType, options.argsType));
}

function getRealFunc(options) {
    var funcPtr = Module.getExportByName(options.module, options.func);
    return new NativeFunction(funcPtr, options.retType, options.argsType);
}

function hitDSStore(path) {
    return path.endsWith('/.DS_Store')
        && !path.startsWith(cagePath + '/')
        && path.indexOf('/.Trashes/') === -1
        && path.indexOf('/.Trash/') === -1;
}

function makeCagePath(path) {
    // return cagePath + '/' + path.substr(0, path.length - 9) + "_DS_Store";
    // TODO 
    // /a/b/c/.DS_Store --> $cagePath/__a__b__c__.DS_Store
    // /a__b__c/.DS_Store --> $cagePath/__a__b__c__.DS_Store
    // collision may occured, need fix this
    return cagePath + '/' + path.replace(/\//g, '__');
}

function ensureDirForPath(file) {
    // TODO already do this in python...
    return true;
}

var real_remove = getRealFunc({
    module: null,
    func: 'remove',
    retType: 'int',
    argsType: ['pointer'],
});

replaceFunc({
    module: null,
    func: 'open',
    retType: 'int',
    argsType: ['pointer', 'int', 'uint16'],
    replace: function (args, realFunc) {
        var path = args[0].readUtf8String();
        var flags = args[1];
        var mode = args[2];

        if (hitDSStore(path)) {
            console.log(
                '!!! open('
                + 'path="' + path + '"'
                + ', flags=' + flags
                + ', mode=' + mode
                + ')'
            );
            var fakePath = makeCagePath(path);
            if (ensureDirForPath(fakePath)) {
                console.log('!!! replace "' + path + '" to "' + fakePath + '"');
                args[0] = Memory.allocUtf8String(fakePath);
            } else {
                console.log('!!! ensure dir for path "' + fakePath + '" error!');
            }
        }
        var ret = realFunc.apply(null, args);
        return ret;
    }
});

replaceFunc({
    module: null,
    func: 'openx_np',
    retType: 'int',
    argsType: ['pointer', 'int', 'pointer'],
    replace: function (args, realFunc) {
        var path = args[0].readUtf8String();
        var flags = args[1];
        var sec = args[2];

        if (hitDSStore(path)) {
            console.log(
                '!!! openx_np('
                + 'path="' + path + '"'
                + ', flags=' + flags
                + ', sec=' + sec
                + ')'
            );
            var fakePath = makeCagePath(path);
            if (ensureDirForPath(fakePath)) {
                console.log('!!! replace "' + path + '" to "' + fakePath + '"');
                args[0] = Memory.allocUtf8String(fakePath);
            } else {
                console.log('!!! ensure dir for path "' + fakePath + '" error!');
            }
        }
        var ret = realFunc.apply(null, args);
        return ret;
    }
});

replaceFunc({
    module: null,
    func: 'getattrlist',
    retType: 'int',
    argsType: ['pointer', 'pointer', 'pointer', 'ulong', 'uint'],
    replace: function (args, realFunc) {
        var path = args[0].readUtf8String();
        var alist = args[1];
        var attributeBuffer = args[2];
        var bufferSize = args[3];
        var options = args[4];

        if (hitDSStore(path)) {
            console.log(
                '!!! getattrlist('
                + 'path="' + path + '"'
                + ', alist=' + alist
                + ', attributeBuffer=' + attributeBuffer
                + ', bufferSize=' + bufferSize
                + ', options=' + options
                + ')'
            );
            var fakePath = makeCagePath(path);
            if (ensureDirForPath(fakePath)) {
                console.log('!!! replace "' + path + '" to "' + fakePath + '"');
                args[0] = Memory.allocUtf8String(fakePath);
            } else {
                console.log('!!! ensure dir for path "' + fakePath + '" error!');
            }
        }
        var ret = realFunc.apply(null, args);
        return ret;
    }
});

replaceFunc({
    module: null,
    func: 'setattrlist',
    retType: 'int',
    argsType: ['pointer', 'pointer', 'pointer', 'ulong', 'uint'],
    replace: function (args, realFunc) {
        var path = args[0].readUtf8String();
        var alist = args[1];
        var attributeBuffer = args[2];
        var bufferSize = args[3];
        var options = args[4];

        if (hitDSStore(path)) {
            console.log(
                '!!! setattrlist('
                + 'path="' + path + '"'
                + ', alist=' + alist
                + ', attributeBuffer=' + attributeBuffer
                + ', bufferSize=' + bufferSize
                + ', options=' + options
                + ')'
            );
            var fakePath = makeCagePath(path);
            if (ensureDirForPath(fakePath)) {
                console.log('!!! replace "' + path + '" to "' + fakePath + '"');
                args[0] = Memory.allocUtf8String(fakePath);
            } else {
                console.log('!!! ensure dir for path "' + fakePath + '" error!');
            }
        }
        var ret = realFunc.apply(null, args);
        return ret;
    }
});
