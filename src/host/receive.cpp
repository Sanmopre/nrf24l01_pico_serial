#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <thread>
#include <chrono>

using namespace boost::asio;

int main() {
    std::string pico_port = "/dev/ttyACM0"; // Change this based on your Pico's port
    unsigned int baud_rate = 115200;

    try {
        io_service io;
        serial_port serial(io, pico_port);
        serial.set_option(serial_port_base::baud_rate(baud_rate));
        serial.set_option(serial_port_base::character_size(8));
        serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
        serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
        serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait for connection to stabilize

        // Sending a command (Uncomment if needed)
        // string command = "4\n";
        // write(serial, buffer(command));
        // cout << "Sent command: " << command << endl;

        // Read response from Pico
        char c;
        std::string response;
        while (true) {
            read(serial, buffer(&c, 1)); // Read one character at a time
            if (c == '\n') { // Check for end of line
                std::cout << "Received: " << response << std::endl;
                response.clear();
            } else {
                response += c;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
