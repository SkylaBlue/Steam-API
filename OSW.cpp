#include "C:\Users\Home\Desktop\Computer related things\Steam stuff\SteamWorks\Steamworks.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <tchar.h>


using namespace std;



int main()
{
  string name;

	CSteamAPILoader CSteamAPILoader;
	CreateInterfaceFn Steam3Factory  = CSteamAPILoader.GetSteam3Factory();
	ISteamClient012* ISteamClient    = (ISteamClient012*)Steam3Factory(STEAMCLIENT_INTERFACE_VERSION_012, NULL);
	HSteamPipe s_Pipe                = ISteamClient->CreateSteamPipe();
	HSteamUser s_User				 = ISteamClient->ConnectToGlobalUser(s_Pipe);
	ISteamUser005* ISteamUser05      = (ISteamUser005*)ISteamClient->GetISteamUser(s_User, s_Pipe, STEAMUSER_INTERFACE_VERSION_005);
	ISteamUser016* ISteamUser		 = (ISteamUser016*)ISteamClient->GetISteamUser(s_User, s_Pipe, STEAMUSER_INTERFACE_VERSION_016);
	ISteamFriends001* ISteamFriend01 = (ISteamFriends001*)ISteamClient->GetISteamFriends(s_User, s_Pipe, STEAMFRIENDS_INTERFACE_VERSION_001);
	ISteamFriends013* ISteamFriends  = (ISteamFriends013*)ISteamClient->GetISteamFriends(s_User, s_Pipe, STEAMFRIENDS_INTERFACE_VERSION_013);
	ISteamUtils002* ISteamUtils02    = (ISteamUtils002*)ISteamClient->GetISteamUtils(s_Pipe, STEAMUTILS_INTERFACE_VERSION_002);
	ISteamUtils005* ISteamUtils      = (ISteamUtils005*)ISteamClient->GetISteamUtils(s_Pipe, STEAMUTILS_INTERFACE_VERSION_005);


	/* Credz to Didrole
	for(;;Sleep(1))
	{
	FriendChatMsg_t friendmsg;
	char szMessage[k_cchFriendChatMsgMax + 1];
	EChatEntryType eEntryType;
	int iMessageSize = ISteamFriends->GetFriendMessage(friendmsg.m_ulFriendID, friendmsg.m_iChatID, szMessage, sizeof(szMessage) - 1, &eEntryType);
	szMessage[iMessageSize] = '\0';

	*/

	if (!ISteamUser->BLoggedOn())
	   {
		 cout << "\nYou're not logged on!";
		 exit(1);
	   }

	else
	{
		cout << "--[User Stats]--" << endl << endl;
		switch(ISteamUser05->IsVACBanned(k_EVACBanSource))
		{
			case 0:
				cout << "Vac Status: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "Clean" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				break;
			case 1:
				cout << "Vac Status: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "Banned" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				break;
		}

		cout << "Country: " << ISteamUtils02->GetIPCountry() << endl;
		cout << "Your STEAMID: " << ISteamUser->GetSteamID() << endl;
		cout << "Your community id: " << ISteamUser->GetSteamID().ConvertToUint64();

		switch(ISteamFriends->GetPersonaState())
		{
			case k_EPersonaStateOnline:
				cout << endl << "User is online";
				break;

			case k_EPersonaStateOffline:
				cout << endl << "User is offline";
				break;

			case k_EPersonaStateAway:
				cout << endl << "User is away";
				break;

			case k_EPersonaStateBusy:
				cout << endl << "User is busy";
				break;
		}


		cout << endl << "Friend count: " << ISteamFriends->GetFriendCount(k_EFriendFlagImmediate) << endl << endl;
	        cout << "--[Your Friends]--" << endl;
		cout << endl << "isInGame?         ||          Handle           ||        Chat ID" << endl;
		for (int i=0; i<ISteamFriends->GetFriendCount(k_EFriendFlagImmediate); i++)
		{
			if(ISteamFriends->GetFriendGamePlayed(ISteamFriends->GetFriendByIndex(i, k_EFriendFlagImmediate), NULL))
			   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

			   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			switch(ISteamFriends->GetFriendPersonaState(ISteamFriends->GetFriendByIndex(i,k_EFriendFlagImmediate)))
			{
				case k_EPersonaStateOnline:
					if(ISteamFriends->GetFriendGamePlayed(ISteamFriends->GetFriendByIndex(i, k_EFriendFlagImmediate), NULL))
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Colour is Green
						cout << endl << "*In Game* ";
						cout << "[Online]  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Colour is White
						break;
					}
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						cout << endl << "\t  [Online]  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Colour is White
						break;


				case k_EPersonaStateOffline:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Colour is Red
					cout << endl << "\t  [Offline] ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					break;

				case k_EPersonaStateAway:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); // Colour is Purple
					cout << endl << "\t  [Away]    ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					break;

				case k_EPersonaStateBusy:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << endl << "\t  [Busy]    ";
					break;

				case k_EPersonaStateSnooze:
					cout << endl << "\t  [Snooze]  ";
					break;

				case k_EPersonaStateLookingToTrade:
					cout << endl << "[L2Trade] ";
					break;

				case k_EPersonaStateLookingToPlay:
					cout << endl << "[L2Play] ";
					break;

				case k_EPersonaStateMax:
					cout << endl << "[Max] ";
					break;
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Colour is bright Cyan
			cout << "Name: " << ISteamFriends->GetFriendPersonaName( ISteamFriends->GetFriendByIndex(i, k_EFriendFlagImmediate));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "  [Chat ID]:" << i;
		}

		while(true)
		{
		 int choice;
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		 cout << endl << endl << "1->Change Name\n2->Single Chat\n3->Global Chat\n4->Status Spam\nChoice: ";
		 cin >> choice;
		 cin.ignore();
		 if (choice == 1)
		 {
			do
			{
				cout << endl << "Enter a name: ";
				getline(cin, name);
				ISteamFriends->SetPersonaName(name.c_str());
			}
			while(name != "Quit" || "quit" || "QUIT" || "Q" || "q");
		 }

		 else if (choice == 2)
		 {
			string message, cool;
			int id;
			string logo = "[VorteX]: ";
			
			cout << endl << "ID: ";
			cin >> id;
			cin.ignore();
			
			do
			{
				cout << endl << "[Message]: ";
				getline(cin, message);
				cool = logo + message;
				ISteamFriends->ReplyToFriendMessage(ISteamFriends->GetFriendByIndex(id, k_EFriendFlagImmediate), cool.c_str());
			}
			while(message != "Quit");
			continue;
		}

		else if(choice == 3)
		{
			string message, gCool;
			string global = "[Global]: ";

			do
			{
				cout << endl << "Message: ";
				getline(cin, message);
				gCool = global + message;

				for (int j = 0; j <ISteamFriends->GetFriendCount(k_EFriendFlagImmediate); j++)
				{
					ISteamFriends->ReplyToFriendMessage(ISteamFriends->GetFriendByIndex(j, k_EFriendFlagImmediate), gCool.c_str());
				}
			}
			while(message != "Quit" || "quit" || "QUIT" || "Q" || "q");	  
			break;
		 }

		else if(choice == 4)
		 {
			int iSpam;

			do
			{
				cout << "How many times to spam: ";
				cin >> iSpam;
				cin.ignore();

				for (int l = 0; l<iSpam; l++)
					{
						Sleep(300);
						EPersonaState eState = (EPersonaState)l;
						ISteamFriend01->SetPersonaState(eState);
					}
			}
			while(iSpam != 1337);
			break;
		}

		else
		  {
			cout << "Enter 1, 2, 3, 4!";
			break;
		  }

			continue;

		 //if(ISteamFriends->GetFriendMessage(friendmsg.m_ulSenderID, friendmsg.m_iChatID, NULL, 0,  EChatEntryType entryType))


	    }

	getchar();
	return 0;
	}
}

