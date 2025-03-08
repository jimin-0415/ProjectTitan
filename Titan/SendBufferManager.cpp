/**********************************************************************************************************************
* @file  SendBufferManager.cpp
*
* @brief SendBufferManager 클래스 cpp 파일
*
* @date  2025.03.03
**********************************************************************************************************************/


#include "pch.h"
#include "SendBufferManager.h"
#include "SendBufferChunk.h"


/**********************************************************************************************************************
* @brief 버퍼를 연다
**********************************************************************************************************************/
SendBufferPtr SendBufferManager::Open( ExInt32 size )
{
    if ( LSendBufferChunk == nullptr )
    {
        LSendBufferChunk = Pop();
        LSendBufferChunk->Reset();
    }
    
    ASSERT_CRASH( false == LSendBufferChunk->IsOpen() );

    // 다 쓰면 새거로 교체
    if ( LSendBufferChunk->FreeSize() < (ExUInt32)size )
    {
        LSendBufferChunk = Pop();
        LSendBufferChunk->Reset();
    }

    cout << "FREE: " << LSendBufferChunk->FreeSize() << endl;

    return LSendBufferChunk->Open( size );
}

/**********************************************************************************************************************
* @brief 버퍼를 추가한다
**********************************************************************************************************************/
ExVoid SendBufferManager::Push( SendBufferChunkPtr buffer )
{
    WRITE_LOCK;
    _sendBufferChunkList.push_back( buffer );
}

/**********************************************************************************************************************
* @brief 버퍼를 꺼낸다
**********************************************************************************************************************/
SendBufferChunkPtr SendBufferManager::Pop()
{
    {
        WRITE_LOCK;
        cout << "pop Chunk!!" << endl;
        if ( _sendBufferChunkList.empty() == false )
        {
            SendBufferChunkPtr sendBufferChunk = _sendBufferChunkList.back();
            _sendBufferChunkList.pop_back();
            return sendBufferChunk;
        }
    }

    cout << "create Chunk!!" << endl;
    return SendBufferChunkPtr( new SendBufferChunk(), PushGlobal );
}

/**********************************************************************************************************************
* @brief 버퍼를 추가한다(재사용)
**********************************************************************************************************************/
ExVoid SendBufferManager::PushGlobal( SendBufferChunk* buffer )
{
    cout << "push Chunk!!" << endl;

    // buffer 재사용
    GSendBufferManager->Push( shared_ptr<SendBufferChunk>( buffer, PushGlobal ) );
}
