#include "VisualBoard.h"

VisualBoard::VisualBoard(/* args */)
{

    game_state = Ready;

    score = 0;

    board = new Board();

    separator = BaseObject(5);

    // inspect generated map
    std::vector<std::pair<Bubble *, std::pair<int, int>>> observation = board->observeBoard();
    cannon = Cannon();
    while (!observation.empty())
    {
        bubblez.push_back(observation.back().first);
        bubble_alias[observation.back().second.first][observation.back().second.second] = observation.back().first;
        observation.pop_back();
    }
    // Bubble to launch
    srand(clock());
    bubblez.push_back(new Bubble(BUBBLE_RADIUS, BUBBLE_LAUNCH_X_COORD, BUBBLE_LAUNCH_Y_COORD, rand() % 5));
    // Bubble to launch next
    bubblez.push_back(new Bubble(BUBBLE_RADIUS, BUBBLE_NEXT_LAUNCH_X_COORD, BUBBLE_NEXT_LAUNCH_Y_COORD, rand() % 5));

    // manage iterator
    to_launch = bubblez.end() - 2;
    next_launch = bubblez.end() - 1;
}

VisualBoard::~VisualBoard()
{
    delete board;

    Bubble *destructor_tmp;
    while (!bubblez.empty())
    {
        destructor_tmp = bubblez.back();
        bubblez.pop_back();
        delete destructor_tmp;
    }
}

void VisualBoard::levelDown()
{
    for (auto bub : bubblez)
    {
        bub->moveRel(0, -BUBBLE_RADIUS * 2);
    }
}

void VisualBoard::launchBubble()
{
    if (game_state == Ready)
    {
        // bubble launch
        (*to_launch)->setState(Moving, BUBBLE_SPEED_MULTIPLIER * cos(cannon.getAngle()), BUBBLE_SPEED_MULTIPLIER * sin(cannon.getAngle()));
        // prepare next launch bubble
        (*next_launch)->moveAbs(BUBBLE_LAUNCH_X_COORD, BUBBLE_LAUNCH_Y_COORD);
        // insert bubble and manage iterator
        bubblez.push_back(generateBubble());
        flying_now = to_launch;
        to_launch += 1;
        next_launch += 1;
        game_state = ShotFlying;
    }
}

// Bubble state transitions
void VisualBoard::stateTransition()
{
    if (game_state == ShotFlying)
    {
        // Move flying bubble
		(*flying_now)->move();
        // collision resolution every times
        collision_pair = board->collision((*flying_now));
        if (collision_pair.first > 0 || collision_pair.second > 0)
        {
            (*flying_now)->setState(Static);
            game_state = ShotCollide;
        }
    }
    else if (game_state == ShotCollide)
    {
        // Collision resolution and transition to next state
        std::pair<double, double> coord_tmp = board->getCoords(collision_pair.first, collision_pair.second);
        (*flying_now)->moveAbs(coord_tmp.first, coord_tmp.second);
        bubble_alias[collision_pair.first][collision_pair.second] = (*flying_now);
        game_state = Pop;
    }
    else if (game_state == Pop)
    {
        int previous_size = bubblez.size();
        // update all bubble states
        for (unsigned int i = 0; i < bubblez.size(); i++)
        {
            bubblez[i]->move();
        }
        pop_vector = board->BubblePop((*flying_now));
        while (!pop_vector.empty())
        {
            tmp = pop_vector.back();
            pop_vector.pop_back();

// ******************************************************************************************8
// 새 객체를 bubblez에 넣지 않는 방향으로 바꿨습니다.
            for (unsigned int i = 0; i < bubblez.size(); i++)
            {
                if (bubblez[i] == bubble_alias[tmp.first][tmp.second])
                {
                    // GC를 Drop state의 끝에서 해줌
                    // 새 객체를 생성할 필요가 없음
                    // bubblez[i].makePopping();
                    bubblez[i]->makePopping();
                    // makePopping(bubblez[i]);
                    // bubblez.erase(bubblez.begin() + i);
                    // delete bubble_alias[tmp.first][tmp.second];
                    bubble_alias[tmp.first][tmp.second] = NULL;
                    break;
                }
            }

// ******************************************************************************************8

        }
        next_launch = bubblez.end() - 1;
        to_launch = next_launch - 1;

        if (previous_size - bubblez.size() > 0)
        {
            score += POINTS_PER_BUBBLE * (previous_size - bubblez.size());
        }

        game_state = Drop;
    }
    else if (game_state == Drop)
    {
        int previous_size = bubblez.size();

        // update all bubble states
        for (unsigned int i = 0; i < bubblez.size(); i++)
        {
            bubblez[i]->move();
        }
        // drop
        drop_vector = board->BubbleDropRC();
        bool state_transition = true;
        if (!drop_vector.empty())
        {
            while (!drop_vector.empty())
            {
                tmp = drop_vector.back();
                drop_vector.pop_back();
                for (unsigned int i = 0; i < bubblez.size(); i++)
                {
                    if (bubblez[i] == bubble_alias[tmp.first][tmp.second])
                    {
                        bubblez[i]->setState(Flick);
                        bubble_alias[tmp.first][tmp.second] = NULL;
                        break;
                    }
                }
            }
            state_transition = false;
        }

        // delete dead bubbles
        for (unsigned int i = 0; i < bubblez.size(); i++)
        {
            if (bubblez[i]->getState() == Dead)
                dead_bubble_stack.push_back(i);
        }
        while (!dead_bubble_stack.empty())
        {
            delete bubblez[dead_bubble_stack.back()];
            bubblez.erase(bubblez.begin() + dead_bubble_stack.back());
            dead_bubble_stack.pop_back();
        }

        // If specific condition is satisfied -> transit state to Ready
        for (unsigned int i = 0; i < bubblez.size(); i++)
        {
            if (bubblez[i]->getState() != Static)
            {
                state_transition = false;
                break;
            }
        }


        // Delete pop bubbles


        next_launch = bubblez.end() - 1;
        to_launch = next_launch - 1;
        if (previous_size - bubblez.size() > 0)
        {
            score += POINTS_PER_BUBBLE * (previous_size - bubblez.size());
        }
        if (state_transition)
            game_state = Ready;
    }
    // Ready state
    else
    {
    }
}

void VisualBoard::draw()
{
    // draw and update all values
    for (unsigned int i = 0; i < bubblez.size() - 2; i++)
    {
        bubblez[i]->draw();
    }
    // glPopMatrix();
    // glPushMatrix();
    for (unsigned int i = bubblez.size() - 2; i < bubblez.size(); i++)
    {
        bubblez[i]->draw();
    }
    cannon.draw();

    // draw separator

    // TODO: BaseObject to other section
    glPushMatrix();
        separator.drawMaterialOnly();
        glBegin(GL_QUADS);
        glVertex3f(-WIDTH,-128,0);
        glVertex3f(-WIDTH,-130, 0);
        glVertex3f(WIDTH, -130, 0);
        glVertex3f(WIDTH, -128, 0);
        glEnd();
    glPopMatrix();

}

void VisualBoard::updateCannonAngle(double theta)
{
    // std::cout << cannon.getAngle() << std::endl;
    cannon.updateAngle(theta);
}

Bubble *VisualBoard::generateBubble()
{
    // TOFIX: generation method
    srand(clock());
    int cnt[5] = {
        0,
    };
    int cnt1 = 0;
    for (unsigned int i = 0; i < bubblez.size() - 2; i++)
        cnt[bubblez[i]->getOption()]++;
    for (int i = 1; i < 5; i++)
        cnt[i] += cnt[i - 1];
    int r = rand() % cnt[4];
    // for (int i = 0; i < 5; i++)
        // std::cout << cnt[i] << ' ';
    // std::cout << r << '\n';
    for (int i = 0; i < 5; i++)
    {
        if (r < cnt[i])
            return new Bubble(BUBBLE_RADIUS, BUBBLE_NEXT_LAUNCH_X_COORD, BUBBLE_NEXT_LAUNCH_Y_COORD, i);
    }
    return new Bubble(BUBBLE_RADIUS, BUBBLE_NEXT_LAUNCH_X_COORD, BUBBLE_NEXT_LAUNCH_Y_COORD, -1);
}

unsigned int VisualBoard::getScore() const
{
    return score;
}

int VisualBoard::getState()
{
    return game_state;
}

bool VisualBoard::gameClear()
{
    return bubblez.size() == 2;
}

bool VisualBoard::gameOver(int clear)
{
    /*for (int i = 0; i < bubblez.size() - 2; i++) {
		double y = bubblez[i]->getY();
		if (y + clear < -300)	return true;
	}*/
    return false;
}

std::deque<Bubble *> VisualBoard::getBubble()
{
    return bubblez;
}

// void VisualBoard::makePopping(Bubble *b)
// {
//     double x = b->getX();
//     double y = b->getY();
//     for (int i = 0; i < 20; i++)
//     {
//         double theta = 2 * M_PI / 20 * i;
//         double r = 20;
//         double dx = x + r * sin(theta);
//         double dy = y + r * cos(theta);
//         Bubble *newBubble = new Bubble(3, dx, dy, b->getOption());
//         newBubble->setState(Popping);
//         newBubble->setGradient(5 * sin(theta), 5 * cos(theta));
//         bubblez.push_back(newBubble);
//     }
// }