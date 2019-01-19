#pragma once

//-------------------------------------------------------
// These classes represent callback functions
//-------------------------------------------------------
class CallBack
{
public:
	virtual void run(void* ctx) = 0;
};
//-------------------------------------------------------
class FuncCallBack : CallBack
{
public:
	FuncCallBack(void(*func)(void*)) : mFunc(func) {}
	void run(void* ctx) override { (*mFunc)(ctx); }
private:
	void(*mFunc)(void*);
};
//-------------------------------------------------------
template<class T>
class MethodCallBack : public CallBack
{
public:
	MethodCallBack(T* obj, void(T::*func)(void*)) : mObj(obj), mFunc(func) {}
	void run(void* ctx) override { (mObj->*mFunc)(ctx); }
private:
	T* mObj;
	void(T::*mFunc)(void*);
};
//-------------------------------------------------------
