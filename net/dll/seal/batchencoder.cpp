// STD
#include <vector>

// SEALDll
#include "stdafx.h"
#include "batchencoder.h"
#include "utilities.h"

// SEAL
#include "seal/batchencoder.h"

using namespace std;
using namespace seal;
using namespace seal::dll;


SEALDLL HRESULT SEALCALL BatchEncoder_Create(void* context, void** batch_encoder)
{
    const auto& sharedctx = SharedContextFromVoid(context);
    IfNullRet(sharedctx, E_POINTER);
    IfNullRet(batch_encoder, E_POINTER);

    try
    {
        BatchEncoder* encoder = new BatchEncoder(sharedctx);
        *batch_encoder = encoder;
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Destroy(void* thisptr)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);

    delete encoder;
    return S_OK;
}

SEALDLL HRESULT SEALCALL BatchEncoder_Encode1(void* thisptr, int count, uint64_t* values, void* destination)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(values, E_POINTER);
    Plaintext* plain = FromVoid<Plaintext>(destination);
    IfNullRet(plain, E_POINTER);

    vector<uint64_t> valvec(count);
    for (int i = 0; i < count; i++)
    {
        valvec[i] = values[i];
    }

    try
    {
        encoder->encode(valvec, *plain);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Encode2(void* thisptr, int count, int64_t* values, void* destination)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(values, E_POINTER);
    Plaintext* plain = FromVoid<Plaintext>(destination);
    IfNullRet(plain, E_POINTER);

    vector<int64_t> valvec(count);
    for (int i = 0; i < count; i++)
    {
        valvec[i] = values[i];
    }

    try
    {
        encoder->encode(valvec, *plain);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Encode3(void* thisptr, void* plain, void* pool)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    try
    {
        encoder->encode(*plainptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Decode1(void* thisptr, void* plain, int* count, uint64_t* destination, void* pool)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(count, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    try
    {
        vector<uint64_t> result;
        encoder->decode(*plainptr, result, *handle);

        *count = static_cast<int>(result.size());

        if (nullptr == destination)
        {
            // We only wanted the count.
            return S_OK;
        }

        for (int i = 0; i < *count; i++)
        {
            destination[i] = result[i];
        }

        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Decode2(void* thisptr, void* plain, int* count, int64_t* destination, void* pool)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(count, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    try
    {
        vector<int64_t> result;
        encoder->decode(*plainptr, result, *handle);

        *count = static_cast<int>(result.size());

        if (nullptr == destination)
        {
            // We only wanted the count.
            return S_OK;
        }

        for (int i = 0; i < *count; i++)
        {
            destination[i] = result[i];
        }

        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_Decode3(void* thisptr, void* plain, void* pool)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    Plaintext* plainptr = FromVoid<Plaintext>(plain);
    IfNullRet(plainptr, E_POINTER);
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(pool);
    if (nullptr == handle)
        handle = &MemoryManager::GetPool();

    try
    {
        encoder->decode(*plainptr, *handle);
        return S_OK;
    }
    catch (const invalid_argument&)
    {
        return E_INVALIDARG;
    }
}

SEALDLL HRESULT SEALCALL BatchEncoder_GetSlotCount(void* thisptr, int* slot_count)
{
    BatchEncoder* encoder = FromVoid<BatchEncoder>(thisptr);
    IfNullRet(encoder, E_POINTER);
    IfNullRet(slot_count, E_POINTER);

    *slot_count = static_cast<int>(encoder->slot_count());
    return S_OK;
}