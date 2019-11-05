#include "VisualBoard.h"


VisualBoard::VisualBoard(/* args */)
{
    // // 발사중인가?
    // isShot = false;
    // // pop 할 게 있는가?
    // isPop = false;
    // // 발사 이후 뭔가 일어나는가?
    // isTransition = false;
    game_state = Ready;


    board = new Board();
    // inspect generated map
    std::vector<std::pair<Bubble*, std::pair<int, int>>> observation = board->observeBoard();
    cannon = Cannon();
    while(!observation.empty()){
        bubblez.push_back(observation.back().first);
        bubble_alias[observation.back().second.first][observation.back().second.second] = observation.back().first;
        observation.pop_back();
    }
    // Bubble to launch
    srand(clock());
    bubblez.push_back(new Bubble(BUBBLE_RADIUS, BUBBLE_LAUNCH_X_COORD, BUBBLE_LAUNCH_Y_COORD, rand()%5));
    // Bubble to launch next
    bubblez.push_back(new Bubble(BUBBLE_RADIUS, BUBBLE_NEXT_LAUNCH_X_COORD, BUBBLE_NEXT_LAUNCH_Y_COORD, rand()%5));

    // manage iterator
    to_launch = bubblez.end()-2;
    next_launch = bubblez.end()-1;
}

VisualBoard::~VisualBoard()
{
    delete board;

    Bubble* tmp;
    while(!bubblez.empty()){
        tmp = bubblez.back();
        bubblez.pop_back();
        delete tmp;
    }
}

void VisualBoard::levelDown(){
    for (auto bub : bubblez) {
        bub->moveRel(0, -50);
    }
}

void VisualBoard::launchBubble(){
    // 게임이 대기 상태일 때 발사 가능
    if(game_state == Ready){
        // bubble launch
        (*to_launch)->setState(Moving, BUBBLE_SPEED_MULTIPLIER * std::cos(cannon.getAngle()), BUBBLE_SPEED_MULTIPLIER * std::sin(cannon.getAngle()));
        // prepare next launch bubble
        (*next_launch)->moveAbs(BUBBLE_LAUNCH_X_COORD, BUBBLE_LAUNCH_Y_COORD);
        // insert bubble and manage iterator
        bubblez.push_back(generateBubble());
        flying_now = to_launch;
        to_launch++;
        next_launch++;
        game_state = ShotFlying;
    }
}


// Bubble state transitions
void VisualBoard::stateTransition(){
    if (game_state == ShotFlying){
        // Move flying bubble
        (*flying_now)->move();
        // collision resolution every times
        collision_pair = board->collision((*flying_now));
        if (collision_pair.first > 0 || collision_pair.second > 0){
            (*flying_now)->setState(Static);
            game_state = ShotCollide;
        }
    }
    else if (game_state == ShotCollide){
        // Collision resolution and transition to next state
        std::pair<double, double> coord_tmp = board->getCoords(collision_pair.first, collision_pair.second);
        (*flying_now)->moveAbs(coord_tmp.first, coord_tmp.second);
        bubble_alias[collision_pair.first][collision_pair.second] = (*flying_now);
        game_state = Pop;
    }
    else if (game_state == Pop){
        // update all bubble states
        for (unsigned int i = 0 ; i < bubblez.size() ; i++){
            bubblez[i]->move();
        }
        pop_vector = board->BubblePop((*flying_now));
        while(!pop_vector.empty()){
            tmp = pop_vector.back();
            pop_vector.pop_back();
            for(unsigned int i = 0 ; i < bubblez.size() ; i++){
                if (bubblez[i] == bubble_alias[tmp.first][tmp.second]){
                    bubblez.erase(bubblez.begin()+i);
                    delete bubble_alias[tmp.first][tmp.second];
                    bubble_alias[tmp.first][tmp.second] = NULL;
                    break;
                }
            }
        }
        next_launch = bubblez.end()-1;
        to_launch = next_launch-1;
        // to_launch = to_launch-pop_size;


        game_state = Drop;
        

    }
    else if(game_state == Drop){
        // update all bubble states
        for (unsigned int i = 0 ; i < bubblez.size() ; i++){
            bubblez[i]->move();
        }
        // drop
        drop_vector = board->BubbleDropRC();
        bool state_transition = true;
        if(!drop_vector.empty()){
            while(!drop_vector.empty()){
                tmp = drop_vector.back();
                drop_vector.pop_back();
                for(unsigned int i = 0 ; i < bubblez.size() ; i++){
                    if (bubblez[i] == bubble_alias[tmp.first][tmp.second]){
                        bubblez[i]->setState(Flick);
                        bubble_alias[tmp.first][tmp.second] = NULL;
                        break;
                    }
                }
            }
            state_transition = false;
        }

        // delete dead bubbles
        for(unsigned int i = 0 ; i < bubblez.size() ; i++){
            if(bubblez[i]->getState() == Dead) dead_bubble_stack.push_back(i);
        }
        while(!dead_bubble_stack.empty()){
            delete bubblez[dead_bubble_stack.back()];
            bubblez.erase(bubblez.begin() + dead_bubble_stack.back());
            dead_bubble_stack.pop_back();
        }


        // If specific condition is satisfied -> transit state to Ready
        for(unsigned int i = 0 ; i < bubblez.size() ; i++){
            if(bubblez[i]->getState() != Static){
                state_transition = false;
                break;
            }
        }

        next_launch = bubblez.end()-1;
        to_launch = next_launch-1;
        if(state_transition) game_state = Ready;

    }
    // Ready state
    else {

    }
}

void VisualBoard::draw() {
    // draw and update all values
    for (unsigned int i = 0 ; i < bubblez.size() ; i++){
        bubblez[i]->draw();
    }
    cannon.draw();
}

void VisualBoard::updateCannonAngle(double theta){
    cannon.updateAngle(theta);
}



Bubble* VisualBoard::generateBubble(){
	// TOFIX: generation method
    srand(clock());
    return new Bubble(BUBBLE_RADIUS, BUBBLE_NEXT_LAUNCH_X_COORD, BUBBLE_NEXT_LAUNCH_Y_COORD, rand()%5);
}