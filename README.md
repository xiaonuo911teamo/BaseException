# BaseException
适用于C++异常捕获的一个实现方法。里面包含两部分，捕捉异常堆栈信息StackWalk和输出log，两部分都源自git，经过整合，完成了将异常堆栈信息输出到log的目的。

### 使用场景
可用于开发软件中，收集定位异常位置。不需要每个错误都要完整复现。

### 使用方法
参考example.cpp。其中 Logger g_logger("log.txt"); 在BaseException.cpp中也有使用，如果需要更改变量名，需要同步更改。更多关于两个库的使用方法请参照https://github.com/bmoscon/Logger missing。

### 注意事项
在VS中使用，可能需要设置以下几个选项。
"C/C++" - "常规" - "调试信息格式" - "程序数据库"
"C/C++" - "优化" - "优化" - "已禁用 (/Od)"
"链接器" - "调试" - "生成调试信息" - "生成调试信息 (/DEBUG)"

// 工程使用unicode编码，或者需要自行解决convert2string.h中的错误。
