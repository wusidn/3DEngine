#include "Materia.h"

#include <cstring>

using namespace std;

namespace engine
{

    const Materia & Materia::defaultMateria(void)
    {
        static Materia & instance = Materia::create();
        instance.retain();
        return instance;
    }

    Materia::Materia(void)
    {
        _colors = nullptr;
        _colorsCount = 0;
    }

    Materia::~Materia(void)
    {
        clearData();
    }

    const bool Materia::init(void)
    {
        if(!Object::init()){ return false; }

        _materiaType = MateriaType::Purity;
        _color = ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
        return true;
    }

    const bool Materia::color(const ColorRGBA & c)
    {
        //清除数据
        clearData();

        _color = c;
        _materiaType = MateriaType::Purity;
        return true;
    }

    const ColorRGBA & Materia::color(void) const 
    {
        return _color;
    }

    const bool Materia::colors(const ColorRGBA * colors, const unsigned int count)
    {

        if(!colors){ return false; }
        if(!count){ return false; }

        //清除数据
        clearData();

        _colorsCount = count;

        _colors = new ColorRGBA[count];
        memcpy(_colors, colors, sizeof(ColorRGBA) * count);

        return true;
    }

    const ColorRGBA * Materia::colors(void) const 
    {
        return _colors;
    }

    const unsigned int Materia::colorsCount(void) const 
    {
        return _colorsCount; 
    }

    const MateriaType & Materia::materiaType(void) const 
    {
        return _materiaType;
    }

    void Materia::clearData(void)
    {
        if(_colors != nullptr)
        {
            delete[] _colors;
            _colors = nullptr;
            _colorsCount = 0;
        }
    }
}