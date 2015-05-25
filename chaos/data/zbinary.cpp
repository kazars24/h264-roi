#include "zbinary.h"

namespace LibChaos {

ZBinary &ZBinary::fill(ZBinary::zbinary_type dat, zu64 size){
    reserve(size);
    _size = size;
    memset(_data, dat, _size);
    return *this;
}

ZBinary &ZBinary::concat(const ZBinary &other){
    reserve(_size + other._size);
    _alloc->rawcopy(other._data, _data + _size, other._size);
    _size = _size + other._size;
    return *this;
}

void ZBinary::reverse(){
    zbinary_type *buffer = _alloc->alloc(_realsize);
    for(zu64 i = 0; i < _size; ++i){
        buffer[i] = _data[_size - i - 1];
    }
    _alloc->dealloc(buffer);
    _data = buffer;
}

zu64 ZBinary::findFirst(const ZBinary &find) const {
    if(find.size() > _size){
        return none;
    }
    zu64 j = 0;
    zu64 start = none;
    for(zu64 i = 0; i < _size; ++i){
        if(_data[i] == find[j]){
            if(j == find.size() - 1)
                return start;
            if(j == 0)
                start = i;
            ++j;
        } else {
            if(j){
                j = 0;
                i = start + 1;
            }
        }
    }
    return start;
}

ZBinary ZBinary::getSub(zu64 start, zu64 len) const {
    if(start >= _size)
        return ZBinary();
    if(start + len >= _size)
        len = _size - start;
    return ZBinary(_data + start, len);
}

ZBinary ZBinary::fromzu8(zu8 num){
    ZBinary bin(1);
    enczu8(bin._data, num);
    return bin;
}

ZBinary ZBinary::fromzu16(zu16 num){
    ZBinary bin(2);
    enczu16(bin._data, num);
    return bin;
}

ZBinary ZBinary::fromzu32(zu32 num){
    ZBinary bin(4);
    enczu32(bin._data, num);
    return bin;
}

ZBinary ZBinary::fromzu64(zu64 num){
    ZBinary bin(8);
    enczu64(bin._data, num);
    return bin;
}

zu8 ZBinary::tozu8() const {
    zassert(_size == 1);
    return deczu8(_data);
}

zu16 ZBinary::tozu16() const {
    zassert(_size == 2);
    return deczu16(_data);
}

zu32 ZBinary::tozu32() const {
    zassert(_size == 4);
    return deczu32(_data);
}

zu64 ZBinary::tozu64() const {
    zassert(_size == 8);
    return deczu64(_data);
}

ZBinary &ZBinary::nullTerm(){
    if(_size && _data[_size - 1] != 0){
        resize(_size + 1);
        _data[_size - 1] = 0;
    }
    return *this;
}

ZBinary ZBinary::printable() const {
    ZBinary tmp = *this;
    if(_size){
        tmp.nullTerm();
        for(zu64 i = 0; i < _size - 1; ++i){
            if(_data[i] == 0){
                _data[i] = '0';
            } else if(_data[i] > 127){
                _data[i] = '!';
            }
        }
    }
    return tmp;
}

zu64 ZBinary::read(zbyte *dest, zu64 length){
    if(_rwpos + length > size())
        length = _rwpos + length - size();
    if(dest && length)
        memcpy(dest, _data + _rwpos, length);
    _rwpos += length;
    return length;
}

zu64 ZBinary::write(const zbyte *data, zu64 size){
    if(size > _size - _rwpos)
        resize(_rwpos + size);
    memcpy(_data + _rwpos, data, size);
    _rwpos += size;
    return size;
}

zu8 ZBinary::readzu8(){
    zassert((_size - _rwpos) >= 1);
    zu8 num = deczu8(_data + _rwpos);
    _rwpos += 1;
    return num;
}
zu16 ZBinary::readzu16(){
    zassert((_size - _rwpos) >= 2);
    zu16 num = deczu16(_data + _rwpos);
    _rwpos += 2;
    return num;
}
zu32 ZBinary::readzu32(){
    zassert((_size - _rwpos) >= 4);
    zu32 num = deczu32(_data + _rwpos);
    _rwpos += 4;
    return num;
}
zu64 ZBinary::readzu64(){
    zassert((_size - _rwpos) >= 8);
    zu64 num = deczu64(_data + _rwpos);
    _rwpos += 8;
    return num;
}

void ZBinary::writezu8(zu8 num){
    resize(_size + 1);
    enczu8(_data + _rwpos, num);
    _rwpos += 1;
}
void ZBinary::writezu16(zu16 num){
    resize(_size + 2);
    enczu16(_data + _rwpos, num);
    _rwpos += 2;
}
void ZBinary::writezu32(zu32 num){
    resize(_size + 4);
    enczu32(_data + _rwpos, num);
    _rwpos += 4;
}
void ZBinary::writezu64(zu64 num){
    resize(_size + 8);
    enczu64(_data + _rwpos, num);
    _rwpos += 8;
}

zu16 ZBinary::readle16(){
    zassert((_size - _rwpos) >= 2);
    zu16 num = decle16(_data + _rwpos);
    _rwpos += 2;
    return num;
}
zu32 ZBinary::readle32(){
    zassert((_size - _rwpos) >= 4);
    zu32 num = decle32(_data + _rwpos);
    _rwpos += 4;
    return num;
}
zu64 ZBinary::readle64(){
    zassert((_size - _rwpos) >= 8);
    zu64 num = decle64(_data + _rwpos);
    _rwpos += 8;
    return num;
}

void ZBinary::writele16(zu16 num){
    resize(_size + 2);
    encle16(_data + _rwpos, num);
    _rwpos += 2;
}
void ZBinary::writele32(zu32 num){
    resize(_size + 4);
    encle32(_data + _rwpos, num);
    _rwpos += 4;
}
void ZBinary::writele64(zu64 num){
    resize(_size + 8);
    encle64(_data + _rwpos, num);
    _rwpos += 8;
}

zu8 ZBinary::deczu8(const zbyte *bin){
    return (zu8)bin[0];
}
void ZBinary::enczu8(zbyte *bin, zu8 num){
    bin[0] = (zbyte)num;
}

zu16 ZBinary::decbe16(const zbyte *bin){
    return ((zu16)bin[0] << 8) |
           ((zu16)bin[1]);
}
zu32 ZBinary::decbe32(const zbyte *bin){
    return ((zu32)bin[0] << 24) |
           ((zu32)bin[1] << 16) |
           ((zu32)bin[2] << 8)  |
           ((zu32)bin[3]);
}
zu64 ZBinary::decbe64(const zbyte *bin){
    return ((zu64)bin[0] << 56) |
           ((zu64)bin[1] << 48) |
           ((zu64)bin[2] << 40) |
           ((zu64)bin[3] << 32) |
           ((zu64)bin[4] << 24) |
           ((zu64)bin[5] << 16) |
           ((zu64)bin[6] << 8)  |
           ((zu64)bin[7]);
}

void ZBinary::encbe16(zbyte *bin, zu16 num){
    bin[0] = (zbyte)((num >> 8) & 0xFF);
    bin[1] = (zbyte)((num)      & 0xFF);
}
void ZBinary::encbe32(zbyte *bin, zu32 num){
    bin[0] = (zbyte)((num >> 24) & 0xFF);
    bin[1] = (zbyte)((num >> 16) & 0xFF);
    bin[2] = (zbyte)((num >> 8)  & 0xFF);
    bin[3] = (zbyte)((num)       & 0xFF);
}
void ZBinary::encbe64(zbyte *bin, zu64 num){
    bin[0] = (zbyte)((num >> 56) & 0xFF);
    bin[1] = (zbyte)((num >> 48) & 0xFF);
    bin[2] = (zbyte)((num >> 40) & 0xFF);
    bin[3] = (zbyte)((num >> 32) & 0xFF);
    bin[4] = (zbyte)((num >> 24) & 0xFF);
    bin[5] = (zbyte)((num >> 16) & 0xFF);
    bin[6] = (zbyte)((num >> 8)  & 0xFF);
    bin[7] = (zbyte)((num)       & 0xFF);
}

zu16 ZBinary::decle16(const zbyte *bin){
    return ((zu16)bin[1] << 8) |
           ((zu16)bin[0]);
}
zu32 ZBinary::decle32(const zbyte *bin){
    return ((zu32)bin[3] << 24) |
           ((zu32)bin[2] << 16) |
           ((zu32)bin[1] << 8)  |
           ((zu32)bin[0]);
}
zu64 ZBinary::decle64(const zbyte *bin){
    return ((zu64)bin[7] << 56) |
           ((zu64)bin[6] << 48) |
           ((zu64)bin[5] << 40) |
           ((zu64)bin[4] << 32) |
           ((zu64)bin[3] << 24) |
           ((zu64)bin[2] << 16) |
           ((zu64)bin[1] << 8)  |
           ((zu64)bin[0]);
}

void ZBinary::encle16(zbyte *bin, zu16 num){
    bin[1] = (zbyte)((num >> 8) & 0xFF);
    bin[0] = (zbyte)((num)      & 0xFF);
}
void ZBinary::encle32(zbyte *bin, zu32 num){
    bin[3] = (zbyte)((num >> 24) & 0xFF);
    bin[2] = (zbyte)((num >> 16) & 0xFF);
    bin[1] = (zbyte)((num >> 8)  & 0xFF);
    bin[0] = (zbyte)((num)       & 0xFF);
}
void ZBinary::encle64(zbyte *bin, zu64 num){
    bin[7] = (zbyte)((num >> 56) & 0xFF);
    bin[6] = (zbyte)((num >> 48) & 0xFF);
    bin[5] = (zbyte)((num >> 40) & 0xFF);
    bin[4] = (zbyte)((num >> 32) & 0xFF);
    bin[3] = (zbyte)((num >> 24) & 0xFF);
    bin[2] = (zbyte)((num >> 16) & 0xFF);
    bin[1] = (zbyte)((num >> 8)  & 0xFF);
    bin[0] = (zbyte)((num)       & 0xFF);
}

float ZBinary::decfloat(const zbyte *bin){
    zu32 n = deczu32(bin);
    if(LIBCHAOS_BIG_ENDIAN){
        return *(float *)&n;
    } else {
        zbyte *rawbe = (zbyte *)&n;
        float out;
        zbyte *raw = (zbyte *)&out;
        raw[0] = rawbe[3];
        raw[1] = rawbe[2];
        raw[2] = rawbe[1];
        raw[3] = rawbe[0];
        return out;
    }
}

double ZBinary::decdouble(const zbyte *bin){
    zu32 n = deczu64(bin);
    if(LIBCHAOS_BIG_ENDIAN){
        return *(double *)&n;
    } else {
        zbyte *rawbe = (zbyte *)&n;
        double out;
        zbyte *raw = (zbyte *)&out;
        raw[0] = rawbe[7];
        raw[1] = rawbe[6];
        raw[2] = rawbe[5];
        raw[3] = rawbe[4];
        raw[4] = rawbe[3];
        raw[5] = rawbe[2];
        raw[6] = rawbe[1];
        raw[7] = rawbe[0];
        return out;
    }
}

void ZBinary::encfloat(zbyte *bin, float flt){
    zbyte *raw;
    if(LIBCHAOS_BIG_ENDIAN){
        raw = (zbyte *)&flt;
    } else {
        zbyte *rawbe = (zbyte *)&flt;
        float out;
        raw = (zbyte *)&out;
        raw[0] = rawbe[3];
        raw[1] = rawbe[2];
        raw[2] = rawbe[1];
        raw[3] = rawbe[0];
    }
    enczu32(bin, *(zu32 *)raw);
}

void ZBinary::encdouble(zbyte *bin, double dbl){
    zbyte *raw;
    if(LIBCHAOS_BIG_ENDIAN){
        raw = (zbyte *)&dbl;
    } else {
        zbyte *rawbe = (zbyte *)&dbl;
        double out;
        raw = (zbyte *)&out;
        raw[0] = rawbe[7];
        raw[1] = rawbe[6];
        raw[2] = rawbe[5];
        raw[3] = rawbe[4];
        raw[4] = rawbe[3];
        raw[5] = rawbe[2];
        raw[6] = rawbe[1];
        raw[7] = rawbe[0];
    }
    enczu64(bin, *(zu64 *)raw);
}

}