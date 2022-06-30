# Acid
## 一个高性能RPC框架


### 模块划分
#### 通用协程同步原语


##### ScopeLock
对信号量（mutex）进行封装，提供三个接口lock、unlock、trylock

##### SpinLock
自旋锁有一个特点，就是不阻塞线程，本项目的同步原语是都是基于自旋锁来实现的，SpinLock简单的封装了posix自旋锁
