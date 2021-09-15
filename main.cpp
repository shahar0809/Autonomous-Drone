

int main() {

    navigator.set_exit_point(FindExit());

    float angle = navigator.calc_rotation_angle();

    tello.SendCommand("cw " + std::to_string(angle));
    while (!(tello.ReceiveResponse()));


    return 0;
}
