#include <atomic>

template<class T>
class shared_ptr
{
public:
    shared_ptr()
    : str_(nullptr)
    {
    }

    shared_ptr(std::nullptr_t)
    : shared_ptr()
    {
    }

    shared_ptr(const shared_ptr& r)
    : str_(r.str_)
    {
        if (str_)
            str_->addref();
    }

    explicit shared_ptr(T* p)
    : shared_ptr()
    {
        if (nullptr == p)
            return;

        try
        {
            str_ = new shared_storage(p);
        }
        catch(...)
        {
            delete p;
            throw;
        }
    }

    ~shared_ptr()
    {
        if (str_)
            str_->release();
    }

    shared_ptr& operator=(const shared_ptr& r)
    {
        shared_ptr(r).swap(*this);
        return *this;
    }

    void swap(shared_ptr& r)
    {
        std::swap(str_, r.str_);
    }

    void reset()
    {
        shared_ptr().swap(*this);
    }

    void reset(T* p)
    {
        shared_ptr(p).swap(*this);
    }

    T& operator*() const
    {
        return *(str_->ptr_);
    }

private:
    class shared_storage
    {
    public:
        shared_storage(T* ptr)
         : cnt_(0)
         , ptr_(ptr)
        {
        }

        void addref()
        {
            ++cnt_;
        }

        void release()
        {
            if (--cnt_ == -1)
            {
                delete ptr_;
                delete this;
            }
        }

        std::atomic_long cnt_;
        T* ptr_;
    };

    shared_storage* str_;
};
