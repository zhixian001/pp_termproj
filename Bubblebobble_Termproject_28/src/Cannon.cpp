#include "Cannon.h"

Cannon::Cannon() : BaseObject(Emerald)
{
    this->head_angle = M_PI / 2;
    this->cone_height = 18;
    this->cylinder_radius = 7.0;
    this->cylinder_depth = 10;
}

Cannon::~Cannon()
{
}

void Cannon::draw()
{
    // TODO: sep
    BaseObject launch_torus = BaseObject(2);

    // launch pnt
    glPushMatrix();
        // drawMaterial();
        glTranslatef(0, BUBBLE_LAUNCH_Y_COORD, this->cylinder_depth);
        // cannon
        glPushMatrix();
            glRotatef(head_angle * 180 / M_PI - 90, 0, 0, 1.0);
            // cannon arrow
            glPushMatrix();
                // glTranslatef(0, 50, 0);
                glPushMatrix();
                    launch_torus.drawMaterialOnly();
                    glutSolidTorus(3, 45, 30, 30);
                glPopMatrix();
                drawMaterial();

                glTranslatef(0, 40, 0);
                glRotatef(-90, 1.0, 0, 0);
                glColor3f(0.7, 0.3, 0.6);
                glutSolidCone(cylinder_radius * 2.3, cone_height, 25, 25);
                // cannon body cylinder
                glPushMatrix();
                    glTranslatef(0, 0, -100);
                    drawCylinder(cylinder_radius, 100.0, 0.7, 0.3, 0.6);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Cannon::updateAngle(double val)
{
    this->head_angle = val;
}

void Cannon::drawCylinder(GLfloat radius, GLfloat height, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    glColor3f(R, G, B);

    // Draw the tube
    // glColor3f(R-0.15625,G-0.15625,B-0.15625);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * M_PI)
    {
        x = radius * std::cos(angle);
        y = radius * std::sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    // Draw the circle on top of cylinder
    // glColor3f(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * M_PI)
    {
        x = radius * std::cos(angle);
        y = radius * std::sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

double Cannon::getAngle() const
{
    return head_angle;
}
