堆

书中的“优先级队列”是基于“完全二叉树”，请基于“完全三叉树”来实现“优先级队列”。

要求使用模板（指定队列中元素的类型为T）定义一个C++类来完成这一任务：
template<class T>
class priqueue {
	priqueue(int maxsize);		// init set S to empty
	void insert(T t);			// add t to S
	T extractmin();				// return smallest in S
};

参考《编程珠玑（第2版）》,ch14-堆
