#ifndef __NET_BUFFER_H__
#define __NET_BUFFER_H__

#include <vector>

class Buffer {
public:
    //typedef std::shared_ptr<Buffer> ptr;
    enum { LEN_SIZE         = 2 };
    enum { ID_SIZE          = 2 };
    enum { CHECKSUM_SIZE    = 4 };
    enum { HEADER_SIZE = LEN_SIZE + ID_SIZE + CHECKSUM_SIZE };

    Buffer(uint16_t capacity = 1024)
        : m_wpos(0)
        , m_rpos(0)
        , m_storage(capacity) {
    }

    ~Buffer() {
    }

    void reset() {
        m_wpos = 0;
        m_rpos = 0;
        m_storage.clear();
    }

    size_t size() {
        return m_storage.size();
    }

    uint16_t remainSpace() {
        return m_storage.size() - m_wpos;
    }

    uint8_t* basePos() {
        //return m_storage.data();
        return &(m_storage[0]);
    }

    uint8_t* readPos() {
        return basePos() + m_rpos;
    }

    uint8_t* writePos() {
        return basePos() + m_wpos;
    }

    void ensureFreeSpace(uint16_t expand) {
        if (remainSpace() < expand) {
            m_storage.resize(m_storage.size() + expand);
        }
    }

    void write(const void* src, int len) {
        ensureFreeSpace(len);
        memmove(writePos(), src, len);
        m_wpos += len;
    }

    template<typename T>
    void push(const T& val) {
        auto size = sizeof(T);
        memmove(writePos(), &val, size);
        m_wpos += size;
    }

    template<typename T>
    T pop() {
        T val;
        auto size = sizeof(T);
        memmove(&val, readPos(), size);
        m_rpos += size;
        return val;
    }

    std::vector<uint8_t>& getStorage() {
		return m_storage;
	}

private:
    uint16_t m_wpos;
    uint16_t m_rpos;
    std::vector<uint8_t> m_storage;
};

#endif
