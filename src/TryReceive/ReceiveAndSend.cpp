// //#pragma comment(lib, "libzmq.lib")//3ashan ye3ml link
// #include <zmq.hpp>
// #include <zmq.h>
// #include <string>
// #include <iostream>
// #ifndef _WIN32
// #include <unistd.h>
// #else
// #include <windows.h>

// #define sleep(n) Sleep(n)
// #endif
// using namespace std;
// void main()
// {

//     cout << "HERE1" << endl;
//     while (1)
//     {
//         zmq::context_t context(1);
//         zmq::socket_t socket(context, ZMQ_REP);
//         socket.bind("tcp://*:5555");
//         zmq_msg_t message;
//         cout << "HERE1" << endl;
//         zmq_msg_init(&message);
//         cout << "HERE1" << endl;
//         zmq_msg_recv(&message, socket, !ZMQ_DONTWAIT); //int zmq_msg_recv (zmq_msg_t *msg, void *socket, int flags);
//         //string s;
//         //memcpy(&s, zmq_msg_data(&message), 4);
//         cout << "HERE1" << endl;
//         size_t MsgSize = zmq_msg_size(&message); //size_t zmq_msg_size (zmq_msg_t *msg);
//         cout << "HERE1" << endl;
//         std::string rpl = std::string(static_cast<char *>(zmq_msg_data(&message)), MsgSize);
//         cout << rpl << endl;
//         //  Process the message frame
//         zmq_msg_close(&message);
//         /*		if (!zmq_msg_more(&message))
// 					break;   */
//         //  Last message frame

//         zmq_msg_t Msg;
//         string ToSendString = "asd/asdas/asdasd";
//         zmq_msg_init_size(&Msg, ToSendString.length());
//         memcpy(zmq_msg_data(&Msg), ToSendString.c_str(), ToSendString.length());
//         zmq_msg_send(&Msg, socket, !ZMQ_DONTWAIT);
//     }
//     system("pause");
//     //while (1) {}
// }
