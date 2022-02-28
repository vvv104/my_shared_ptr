#include <gtest/gtest.h>
#include "shared_ptr.h"
#include <utility>

TEST(shared_ptr, empty_ptr)
{
    // Create an empty (ie. NULL) shared_ptr
    shared_ptr<int> xPtr;

    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());

    // Reset to NULL (ie. do nothing)
    xPtr.reset();

    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());

    // sub-scope
    {
        // Copy construct the empty (ie. NULL) shared_ptr
        shared_ptr<int> yPtr(xPtr);

        EXPECT_EQ(0,     xPtr.use_count());
        EXPECT_EQ((void*)NULL,  xPtr.get());
        EXPECT_EQ(0,     yPtr.use_count());
        EXPECT_EQ((void*)NULL,  yPtr.get());

        // Assign the empty (ie. NULL) shared_ptr
        shared_ptr<int> zPtr;
        zPtr = xPtr;

        EXPECT_EQ(0,     xPtr.use_count());
        EXPECT_EQ((void*)NULL,  xPtr.get());
        EXPECT_EQ(0,     zPtr.use_count());
        EXPECT_EQ((void*)NULL,  zPtr.get());
    }
    // end of scope

    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());
}

TEST(shared_ptr, basic_ptr)
{
    {
        // Create a shared_ptr
        shared_ptr<int> xPtr(new int(123));

        EXPECT_EQ(1,    xPtr.use_count());
        EXPECT_NE((void*)NULL, xPtr.get());

        if (xPtr.get())
        {
            EXPECT_EQ(123,  *xPtr);

            (*xPtr)++;
            EXPECT_EQ(124,  *xPtr);

            // Copy construct the shared_ptr
            shared_ptr<int> yPtr(xPtr);

            EXPECT_EQ(2,     xPtr.use_count());
            EXPECT_NE((void*)NULL,  xPtr.get());

            EXPECT_EQ(2,     yPtr.use_count());
            EXPECT_EQ(124,   *yPtr);
            EXPECT_NE((void*)NULL,  yPtr.get());

            if (yPtr.get())
            {
                // Assign the shared_ptr
                shared_ptr<int> zPtr;
                zPtr = xPtr;

                EXPECT_EQ(3,     xPtr.use_count());
                EXPECT_NE((void*)NULL,  xPtr.get());
                EXPECT_EQ(124,   *xPtr);
                EXPECT_EQ(3,     yPtr.use_count());
                EXPECT_NE((void*)NULL,  yPtr.get());
                EXPECT_EQ(124,   *yPtr);
                EXPECT_EQ(3,     zPtr.use_count());
                EXPECT_NE((void*)NULL,  zPtr.get());
                EXPECT_EQ(124,   *zPtr);
                (*zPtr)++;
            }

            EXPECT_EQ(2,     xPtr.use_count());
            EXPECT_NE((void*)NULL,  xPtr.get());
            EXPECT_EQ(125,   *xPtr);
            *yPtr = 500;
        }
        else
        {
            GTEST_FATAL_FAILURE_("get() error");
        }

        EXPECT_EQ(1,    xPtr.use_count());
        EXPECT_NE((void*)NULL, xPtr.get());
        EXPECT_EQ(500,  *xPtr);
    }
}

TEST(shared_ptr, reset_ptr)
{
    // Create an empty (ie. NULL) shared_ptr
    typedef std::pair<int, int> pair;
    shared_ptr<pair> xPtr;

    // Reset it with a new pointer
    xPtr.reset(new pair(123, 321));

    EXPECT_EQ(1,    xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,  xPtr->first);
    EXPECT_EQ(321,  xPtr->second);
    pair* pX  = xPtr.get();

    // Reset it with another new pointer
    xPtr.reset(new pair(234, 432));

    EXPECT_EQ(1,    xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234,  xPtr->first);
    EXPECT_EQ(432,  xPtr->second);
    EXPECT_NE(pX,   xPtr.get());

    // Copy-construct a new shared_ptr to the same object
    shared_ptr<pair> yPtr(xPtr);

    EXPECT_EQ(2,     xPtr.use_count());
    EXPECT_NE((void*)NULL,  xPtr.get());
    EXPECT_EQ(234,   xPtr->first);
    EXPECT_EQ(2,     yPtr.use_count());
    EXPECT_NE((void*)NULL,  yPtr.get());
    EXPECT_EQ(432,   yPtr->second);

    // Reset to NULL
    yPtr.reset();

    EXPECT_EQ(0,     yPtr.use_count());
    EXPECT_EQ((void*)NULL,  yPtr.get());
    EXPECT_EQ(1,     xPtr.use_count());
    EXPECT_NE((void*)NULL,  xPtr.get());
    EXPECT_EQ(234,   xPtr->first);

    // Copy-construct a new shared_ptr to the same object
    shared_ptr<pair> zPtr(xPtr);

    EXPECT_EQ(2, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->first);
    EXPECT_EQ(2, zPtr.use_count());
    EXPECT_NE((void*)NULL, zPtr.get());
    EXPECT_EQ(432, zPtr->second);

    // Reset it with another new pointer : now xPtr and yPtr each manage a different instance
    zPtr.reset(new pair(345, 543));

    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->first);
    EXPECT_EQ(1, zPtr.use_count());
    EXPECT_NE((void*)NULL, zPtr.get());
    EXPECT_EQ(345, zPtr->first);

    // Reset to NULL
    zPtr.reset();

    EXPECT_EQ(0,     zPtr.use_count());
    EXPECT_EQ((void*)NULL,  zPtr.get());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->first);

    // Reset to NULL
    xPtr.reset();

    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());
}

TEST(shared_ptr, swap_ptr)
{
    // Create a shared_ptr
    shared_ptr<int> xPtr(new int(123));

    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123, *xPtr);
    int* pX = xPtr.get();

    // Create another shared_ptr
    shared_ptr<int> yPtr(new int(234));

    EXPECT_EQ(1, yPtr.use_count());
    EXPECT_NE((void*)NULL, yPtr.get());
    EXPECT_EQ(234, *yPtr);
    int* pY = yPtr.get();

    if (pX < pY)
    {
        EXPECT_LT(*xPtr, *yPtr);
        xPtr.swap(yPtr);
        EXPECT_GT(*xPtr, *yPtr);
    }
    else // (pX > pY)
    {
        EXPECT_GT(*xPtr, *yPtr);
        xPtr.swap(yPtr);
        EXPECT_LT(*xPtr, *yPtr);
    }
}
