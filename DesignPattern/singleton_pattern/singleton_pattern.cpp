#include <iostream>

class Singleton {
public:
    // 静态方法获取唯一实例
    static Singleton* GetInstance() {
        if (_instance == nullptr) {
            _instance = new Singleton();
        }
        return _instance;
    }

    // 示例方法
    void DoSomething() {
        std::cout << "Doing something." << std::endl;
    }

    // 析构函数
    ~Singleton() {
        std::cout << "Singleton instance destroyed." << std::endl;
    }

private:
    // 私有静态实例指针
    static Singleton* _instance;

    // 私有构造函数
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }

    // 删除拷贝构造函数
    Singleton(const Singleton&) = delete;
    // 删除赋值操作符
    Singleton& operator=(const Singleton&) = delete;
};

// 初始化静态成员变量
Singleton* Singleton::_instance = nullptr;

int main() {
    // 获取单例实例
    Singleton* singleton = Singleton::GetInstance();
    // 使用单例实例的方法
    singleton->DoSomething();

    // 再次获取单例实例
    Singleton* singleton2 = Singleton::GetInstance();
    // 检查是否为同一个实例
    if (singleton == singleton2) {
        std::cout << "Both pointers point to the same instance." << std::endl;
    }

    return 0;
}
