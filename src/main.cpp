#include "ui/ui.hpp"
#include "in_out/in_out.hpp"

int main(){
    in_out::read();

    menu::main_screen();

    in_out::write();
    
    return 0;
}