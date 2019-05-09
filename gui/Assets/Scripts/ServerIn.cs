using System.Collections;
using System.Collections.Generic;
using NetMQ;
using NetMQ.Sockets;
using UnityEngine;

/**
 * This class implements the communication logic between the C# scripts used by Unity and the C++ retrived from the server
 * 
 * This code was written on 30/4/2019
 * author:Mohamed Anwar
 * Modified by:@minalouis9
 */

public class ServerIn : MonoBehaviour
{
    static string Best_Word;
    static string Start_Row_From_Program_Best; // ai and trainer
    static string Start_Col_From_Program_Best; // ai and trainer
    static bool Horizontal_From_Program_Best;  // ai and trainer
    static string board;
    static string Rack;  //ai and trainer from c++ 
    static string Word_From_Program; // ai and trainer 
    static string Start_Row_From_Program; // ai and trainer
    static string Start_Col_From_Program; // ai and trainer
    static bool Horizontal_From_Program;  // ai and trainer
    static string Word_From_GUi; // trainer mode only
    static string Start_Row_From_Gui; // trainer mode only
    static string Start_Col_From_Gui; // trainer mode only
    static bool Horizontal_From_Gui; // trainer mode only
    static string turn;// both modes
    static string My_Score; // both modes
    static string Opp_score; //both modes
    static string Time; // both modes
    static string My_Time; // both modes
    static string Opp_Time; // both modes
    static string Exchanged_Value;
    static string Response_on_Move; // trainer mode only
    static bool Ready_to_Recv = false;
    static bool Ready_to_Recv_Best = false;
    static bool Ready_to_Send = false;
    static bool Pass_Move = false;
    static bool Exchange_Move = false;
    static string Message_From_Teacher;

    /// Start of Setters
    public static void Set_Rack(string rack)
    {
        Rack = rack;
    }
    public static void Set_Word_From_Program(string word_From_Program)
    {
        Word_From_Program = word_From_Program;
    }
    public static void Set_Start_Row_From_Program(string start_Row_From_Program)
    {
        Start_Row_From_Program = start_Row_From_Program;
    }
    public static void Set_Start_Col_From_Program(string start_Col_From_Program)
    {
        Start_Col_From_Program = start_Col_From_Program;
    }
    public static void Set_Best_Word(string best_Word)
    {
        Best_Word = best_Word;
    }
    public static void Set_Start_Row_From_Program_Best(string start_Row_From_Program_Best)
    {
        Start_Row_From_Program_Best = start_Row_From_Program_Best;
    }
    public static void Set_Start_Col_From_Program_Best(string start_Col_From_Program_Best)
    {
        Start_Col_From_Program_Best = start_Col_From_Program_Best;
    }
    public static void Set_Word_From_GUi(string word_From_GUi)
    {
        Word_From_GUi = word_From_GUi;
    }
    public static void Set_Start_Row_From_Gui(string start_Row_From_Gui)
    {
        Start_Row_From_Gui = start_Row_From_Gui;
    }
    public static void Set_Start_Col_From_Gui(string start_Col_From_Gui)
    {
        Start_Col_From_Gui = start_Col_From_Gui;
    }
    public static void Set_turn(string Turn)
    {
        turn = Turn;
    }
    public static void Set_My_Score(string my_Score)
    {
        My_Score = my_Score;
    }
    public static void Set_Opp_score(string opp_score)
    {
        Opp_score = opp_score;
    }
    public static void Set_Time(string time)
    {
        Time = time;
    }
    public static void Set_My_Time(string time)
    {
        My_Time = time;
    }
    public static void Set_Opp_Time(string time)
    {
        Opp_Time = time;
    }
    public static void Set_board(string Board)
    {
        board = Board;
    }
    public static void Set_Response_on_Move(string response_on_Move)
    {
        Response_on_Move = response_on_Move;
    }
    public static void Set_Horizontal_From_Program(bool horizontal_From_Program)
    {
        Horizontal_From_Program = horizontal_From_Program;
    }
    public static void Set_Horizontal_From_Program_Best(bool horizontal_From_Program_Best)
    {
        Horizontal_From_Program_Best = horizontal_From_Program_Best;
    }
    public static void Set_Horizontal_From_Gui(bool horizontal_From_GUI)
    {
        Horizontal_From_Gui = horizontal_From_GUI;
    }
    public static void Set_Ready_to_Recv(bool ready_to_Recv)
    {
        Ready_to_Recv = ready_to_Recv;
    }
    public static void Set_Ready_to_Recv_Best(bool ready_to_Recv_Best)
    {
        Ready_to_Recv_Best = ready_to_Recv_Best;
    }
    public static void Set_Ready_to_Send(bool ready_to_Send)
    {
        Ready_to_Send = ready_to_Send;
    }

    public static void Set_Pass_Move(bool pass_Move)
    {
        Pass_Move = pass_Move;
    }
    public static void Set_Exchange_Move(bool exchange_Move)
    {
        Exchange_Move = exchange_Move;
    }
    public static void Set_Message_From_Teacher(string message_From_Teacher)
    {
        Message_From_Teacher = message_From_Teacher;
    }
    public static void Set_Exchanged_Value(string exchanged_Value)
    {
        Exchanged_Value = exchanged_Value;
    }
    /// End OF Setters

    /// Start OF Getters
    public static string Get_Rack()
    {
        return Rack;
    }
    public static string Get_Word_From_Program()
    {
        return Word_From_Program;
    }
    public static string Get_Start_Row_From_Program()
    {
        return Start_Row_From_Program;
    }
    public static string Get_Start_Col_From_Program()
    {
        return Start_Col_From_Program;
    }
    ///////////////////////////////////////
    public static string Get__Best_Word()
    {
        return Best_Word;
    }
    public static string Get_Start_Row_From_Program_Best()
    {
        return Start_Row_From_Program_Best;
    }
    public static string Get_Start_Col_From_Program_Best()
    {
        return Start_Col_From_Program_Best;
    }
    public static string Get_Word_From_GUi()
    {
        return Word_From_GUi;
    }
    public static string Get_Start_Row_From_Gui()
    {
        return Start_Row_From_Gui;
    }
    public static string Get_Start_Col_From_Gui()
    {
        return Start_Col_From_Gui;
    }
    public static string Get_turn()
    {
        return turn;
    }
    public static string Get_Opp_score()
    {
        return Opp_score;
    }
    public static string Get_Time()
    {
        return Time;
    }
    public static string Get_My_Time()
    {
        return My_Time;
    }
    public static string Get_Opp_Time()
    {
        return Opp_Time;
    }
    public static string Get_board()
    {
        return board;
    }
    public static string Get_My_Score()
    {
        return My_Score;
    }
    public static string Get_Response_on_Move()
    {
        return Response_on_Move;
    }
    public static bool Get_Horizontal_From_Program()
    {
        return Horizontal_From_Program;
    }
    public static bool Get_Horizontal_From_Program_Best()
    {
        return Horizontal_From_Program_Best;
    }
    public static bool Get_Horizontal_From_Gui()
    {
        return Horizontal_From_Gui;
    }
    public static bool Get_Ready_to_Recv()
    {
        return Ready_to_Recv;
    }
    public static bool Get_Ready_to_Recv_Best()
    {
        return Ready_to_Recv_Best;
    }
    public static bool Get_Ready_to_Send()
    {
        return Ready_to_Send;
    }
    public static bool Get_Pass_Move()
    {
        return Pass_Move;
    }
    public static bool Get_Exchange_Move()
    {
        return Exchange_Move;
    }
    public static string Get_Message_From_Teacher()
    {
        return Message_From_Teacher;
    }
    public static string Get_Exchanged_Value()
    {
        return Exchanged_Value;
    }
    /// End of Getters
    
    /// Communication Function
    public static void Receive_From_Program()
    {
        AsyncIO.ForceDotNet.Force();
        using (var server = new ResponseSocket())
        {
            //Debug.Log("Using 5raaav ");
            server.Bind("tcp://*:5555");
            //Debug.Log("Using Server");
            while (true)
            {
               // Debug.Log("inside the while loop");
                string Input_From_Program = "";
                //bool IsRecieved = server.TryReceiveFrameString(out Input_From_Program);
                Input_From_Program = server.ReceiveFrameString();
                bool IsRecieved = true;
                if (IsRecieved == true)
                {
                    string trim = Input_From_Program.Trim();
                    //Debug.Log(trim);
                    string[] Parameters_List = Input_From_Program.Split('/');
                    if (Parameters_List[0] == "play" && Parameters_List[1] == "tm")
                    {
                        Debug.Log(trim);
                        Set_turn(Parameters_List[2]); // Turn 
                        Debug.Log(Get_turn());
                        Set_Start_Col_From_Program(Parameters_List[3]); // Col
                        Debug.Log(Get_Start_Col_From_Program());
                        Set_Start_Row_From_Program(Parameters_List[4]); // Row
                        Debug.Log(Get_Start_Row_From_Program());
                        if (Parameters_List[5] == "true")
                        {
                            Set_Horizontal_From_Program(true); // Hor
                        }
                        else if (Parameters_List[5] == "false")
                        {
                            Set_Horizontal_From_Program(false); // Ver
                        }

                        Debug.Log(Get_Horizontal_From_Program());
                        Set_Word_From_Program(Parameters_List[6]); // The new word to be displayed on the board
                        Debug.Log(Get_Word_From_Program());
                        Set_My_Score(Parameters_List[7]); // My Score
                        Debug.Log(Get_My_Score());
                        Set_Opp_score(Parameters_List[8]); // Opp Score
                        Debug.Log(Get_Opp_score());
                        Set_My_Time(Parameters_List[9]); // My Time
                        Debug.Log(Get_My_Time());
                        Set_Opp_Time(Parameters_List[10]); // Opp Time
                        Debug.Log(Get_Opp_Time());
                        Set_Time(Parameters_List[11]); // Total Time
                        Debug.Log(Get_Time());
                        Set_Rack(Parameters_List[12]); // Rack tiles
                        Debug.Log(Get_Rack());
                        Set_Message_From_Teacher(Parameters_List[13]); // Messege received from the teacher in teacher mode
                        Debug.Log(Get_Message_From_Teacher());
                        Set_Ready_to_Recv(true);
                    }
                    else if (Parameters_List[0] == "best" && Parameters_List[1] == "tm")
                    {
                        
                        
                            //Debug.Log(trim);
                            //Set_turn(Parameters_List[2]); // Turn 
                            Debug.Log(Get_turn());
                            Set_Start_Col_From_Program_Best(Parameters_List[3]); // Col
                            Debug.Log(Get_Start_Col_From_Program());
                            Set_Start_Row_From_Program_Best(Parameters_List[4]); // Row
                            Debug.Log(Get_Start_Row_From_Program());
                            if (Parameters_List[5] == "true")
                            {
                                Set_Horizontal_From_Program_Best(true); // Hor
                            }
                            else if (Parameters_List[5] == "false")
                            {
                                Set_Horizontal_From_Program_Best(false); // Ver
                            }

                            Debug.Log(Get_Horizontal_From_Program_Best());
                            Set_Best_Word(Parameters_List[6]); // The new word to be displayed on the board
                            //Debug.Log(Get_Word_From_Program());
                            //Set_My_Score(Parameters_List[7]); // My Score
                            //Debug.Log(Get_My_Score());
                            //Set_Opp_score(Parameters_List[8]); // Opp Score
                            //Debug.Log(Get_Opp_score());
                            //Set_My_Time(Parameters_List[9]); // My Time
                            //Debug.Log(Get_My_Time());
                            //Set_Opp_Time(Parameters_List[10]); // Opp Time
                            //Debug.Log(Get_Opp_Time());
                            //Set_Time(Parameters_List[11]); // Total Time
                            //Debug.Log(Get_Time());
                            //Set_Rack(Parameters_List[12]); // Rack tiles
                            //Debug.Log(Get_Rack());
                            Set_Message_From_Teacher(Parameters_List[13]); // Messege received from the teacher in teacher mode
                            Debug.Log(Get_Message_From_Teacher());
                            Set_Ready_to_Recv_Best(true);
                        

                    }
                    else if (Parameters_List[0] == "board")
                    {
                        Set_board(Parameters_List[1]);
                        Set_Ready_to_Recv(true);
                    }
                    else
                    {
                      //  Set_Ready_to_Recv(false);
                        //Debug.Log(" receive dummy");
                    }
                    //&& Get_Pass_Move() == false && Get_Exchange_Move() == false
                    if (Get_Ready_to_Send() == true )
                    {
                        Debug.Log("start to send");

                        //Set_turn("1"); Set_Start_Col_From_Gui("7"); Set_Start_Row_From_Gui("7"); Set_Horizontal_From_Gui(true); Set_Word_From_GUi("SEVENTY"); Set_My_Score("70"); Set_Opp_score("0"); Set_My_Time("120"); Set_Opp_Time("10"); Set_Time("120"); Set_Rack(""); Set_Message_From_Teacher("Hello from the other side");
                        string Sending_String = "play/"+ Get_Start_Row_From_Gui() + "/" + Get_Start_Col_From_Gui() + "/"  + Get_Horizontal_From_Gui() + "/" + Get_Word_From_GUi() ;
                        string Sending_String_Trim = Sending_String.Trim();
                        Set_Ready_to_Send(false);
                        Debug.Log(Sending_String_Trim);
                        server.SendFrame(Sending_String_Trim);
                        Debug.Log(" send is done");

                        // send function to gui
                    }
                    else if (Get_Ready_to_Send() == true && Get_Pass_Move() == true)
                    {
                        server.SendFrame("####");
                        Set_Pass_Move(false);
                       // Set_Ready_to_Send(false);
                        // send function to gui
                    }
                    else if (Get_Ready_to_Send() == true && Get_Exchange_Move() == true)
                    {
                        server.SendFrame("****" + Get_Exchanged_Value());
                        Set_Pass_Move(false);
                       // Set_Ready_to_Send(false);
                        // send function to gui
                    }
                    else
                    {
                        //Set_Ready_to_Send(false);
                        server.SendFrame("0"); /// send zero if gui is not ready to send
                    }
                }
            }
        }
    }
    
    public static string getTeacherOpinion()
    {
        return Message_From_Teacher;
    }
}
