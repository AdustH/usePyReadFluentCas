#include <Python.h>
#include <iostream>

int main() {
	Py_Initialize();//python初始化

	//初始化python系统文件路径，保证可以访问到 .py文件
	//PyRun_SimpleString：把python代码当作一个字符串传给解释器来执行。
	PyRun_SimpleString("import sys");

	/*把python脚本文件放入当前目录下的PyFiles文件夹下
	sys.path是一个列表 list, 它里面包含了已经添加到系统的环境变量路径。
	当我们要添加自己的引用模块搜索目录时，可以通过列表 list 的 append()方法；*/
	PyRun_SimpleString("sys.path.append('./PyFiles')");

	//PyImport_ImportModule：动态加载python模块，相当于导入python脚本文件
	//调用python文件名。当前的测试python文件名是ReadData。在使用这个函数的时候，只需要写文件的名称就可以了。不用写后缀。
	const char* name_module = "ReadData";
	PyObject* mod = PyImport_ImportModule(name_module);//获取.py文件名，name_module不加.py

	PyObject* func = PyObject_GetAttrString(mod, "get_pressure");//获取py文件中的函数名

	PyObject* tuple = PyTuple_New(3);//新建有两个参数的元组
	PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(0.0));//将参数按照函数的参数顺序添加到元组内
	PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(0.0));
	PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(0.0));//PyTuple_SetItem(元组，元素索引，元素)


	double a = PyFloat_AsDouble(PyObject_CallObject(func, tuple));//运行py中的函数，将返回值赋值给a

	std::cout << a << std::endl;

	Py_Finalize();//清理python内存

	return 0;
}

