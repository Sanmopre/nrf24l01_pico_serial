#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

namespace asio = boost::asio;

int main() {
    std::string pico_port = "/dev/ttyACM0"; // Change based on your Pico's port
    unsigned int baud_rate = 115200;

    try {
        asio::io_service io;
        asio::serial_port serial(io, pico_port);
        serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
        serial.set_option(asio::serial_port_base::character_size(8));
        serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
        serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
        serial.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Stabilization delay

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(2));

            for (int x = 0; x < 5; x++) {
                std::string command = std::to_string(x) + "\n";
                asio::write(serial, asio::buffer(command));
                std::cout << "Sent: " << command;

                // Read response
                asio::streambuf buf;
                boost::system::error_code error;
                size_t len = asio::read_until(serial, buf, "\n", error);

                if (!error) {
                    std::istream is(&buf);
                    std::string response;
                    std::getline(is, response);
                    std::cout << "Received: " << response << std::endl;
                } else {
                    std::cerr << "Error reading: " << error.message() << std::endl;
                }
            }
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}