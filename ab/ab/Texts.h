#pragma once

#include <string>
#include <vector>
#include <GL/glut.h>

class Txt {
private:
    double posiiton[2];

    friend class Texts;
public:
    Txt();
    ~Txt();

};

/* collection of 2D texts */
class Texts {

private:
    double width, height;
    std::vector<Txt*> form_storage;
public:
    Texts(double _width, double _height);

    Txt* addForm(double _pos_x, double _pos_y, void* _font, std::string _text="");
    void updateFormText(Txt* _to_modify, std::string _text);
    void removeForm(Txt* _to_delete);
    void relocateForm(Txt* _to_move, double _pos_x, double _pos_y);


    ~Texts();

};
