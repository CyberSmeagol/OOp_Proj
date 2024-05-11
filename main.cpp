#include<iostream>
#include<vector>
//#include"Header.h"
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

class page;
class activ;
class post;
class comment;
class user {
protected:
	string id;
	string name;
	vector<string> friends_list;
	vector<string> pages_followed; // liked
	bool has_page;
	page* homepage;
	vector<string> posts;
	static int total_users;

public:
	user(string ID = "", string Name = "", vector<string> Friends = {}, vector<string> Pages = {}, vector<string> Posts = {}, bool Has_page = false) : id(ID), name(Name), friends_list(Friends), pages_followed(Pages), posts(Posts), has_page(Has_page) {
		
		
	}

		string getName() { return name; }
		vector<string> getPosts() { return posts; }
		vector<string> getPages() { return pages_followed; }
		vector<string> getFriends() { return friends_list; }
		string getId() { return id; }
};
class page {
protected:
	string id;
	string name;
	string owner;
	vector<string> posts;
	int followers;
	static int total_pages;
public : 
	page(string ID = "", string Name = "", vector<string> Posts = {},string Owner="", int Followers = 0) : id(ID), name(Name), posts(Posts), owner(Owner), followers(Followers) {
	
	}
	vector<string> getPosts(){ return posts; }
	string getId() { return id; }
	string getName() { return name; }
	string getOwner() { return owner; }
	int getFollowers() { return followers; }
};
class activ {
	protected:
		string content;
		int number;
public:
	activ(string Content = "", int Number = 0) : content(Content), number(Number) {}

	string getContent() { return content; }
	int getNumber() { return number; }
};
class kronos {
protected:
	//string timeString;
	int month, date,year, hour, min;

public:
	kronos(struct tm* localTime) {

		date = localTime->tm_mday;
		month = localTime->tm_mon + 1; // tm_mon is 0-indexed, so add 1
		year = localTime->tm_year + 1900; // tm_year is years since 1900
		hour = localTime->tm_hour;
		min = localTime->tm_min;
		/*time_t now = time(0);
		char buffer[30] = {};
		
	timeString = ctime_s(buffer, 30, &now);
	timeString = buffer;*/

	}
	kronos(int Year = 0, int Month = 0, int Date = 0, int Hour = 0, int Min = 0): year(Year), month(Month), date(Date), hour(Hour), min(Min) {

	}
	int getDate() { return date; }
	int getMonth() { return month; }
	int getYear() { return year; }
	//void displayTime() const {
	//	std::cout << "Current date and time: " << timeString;
	//}
};
class post {
protected:
	string id;
	kronos time_added;
	string content;
	activ *activity;
	string owner; // user needed
	int likes;
	static int total_posts;
	vector<string> comments;

public:
	post(string ID = "", int Date = 0, int Month = 0, string Content = "", string Owner = "", int Likes = 0, int activnumber=0, string activcontent = "",vector<string> Comments = {} , int hours = 0, int min = 0, int year =0) : id(ID), content(Content), owner(Owner), likes(Likes), comments(Comments) {
		activity = new activ(activcontent, activnumber);
		time_added = kronos(year,Month, Date, hours, min);
	}
	~post() {};
	
	string getOwner() { return owner; }
	string getId() { return id; }
	int getDate() { return time_added.getDate(); }
	int getMonth() { return time_added.getMonth(); }
	int getYear() { return time_added.getYear(); }
	string getContent() { return content; }
	int getLikes() { return likes; }
	vector<string> getComments() { return comments; }
	activ* getActivity() { return activity; }
	



};
class comment {
protected:
	string id, owner_post, owner_user, content;
	static int total_comments;
public:
	comment(string ID = "", string Owner_Post = "", string Owner_User = "", string Content = "") : id(ID), owner_post(Owner_Post), owner_user(Owner_User), content(Content) {}
	~comment() {};
	string getId() { return id; }
	string getOwnerPost() { return owner_post; }
	string getOwnerUser() { return owner_user; }
	string getContent() { return content; }
};
int post::total_posts = 0;
int user ::total_users = 0;
int page ::total_pages = 0;
int comment ::total_comments = 0;
 class Runner : public user, public page, public post ,public comment {
 public:
	 vector<user>users_list;
	 vector<page>pages_list;
	 vector<post>posts_list;
	 vector<comment>comments_list;
	 vector<post>home_posts;
	 
	void readUsers() {
	//vector<user> users_list;
	fstream users_file("Users.txt");
	

	users_file >> user::total_users;
		for (int i = 0; i < total_users; i++) {
			string id, name, a; vector<string> friends,pages,posts;bool has_page;
			users_file >> id;
			users_file >> name;
			users_file >> a;
			while (a != ";") {
				friends.push_back(a);
				users_file >> a;
					}
				users_file >> a;
			while (a != ";") {
				pages.push_back(a);
				users_file >> a;
						}
			users_file >> a;
			while (a != ";") {
				posts.push_back(a);
				users_file >> a;
			}
			users_file >> has_page;

				users_list.push_back(user(id, name, friends, pages, posts, has_page));
	
		}
	
	}
	void readPages() {
		fstream pages_file("Pages.txt");
		pages_file >> page::total_pages;
		for (int i = 0; i < total_pages; i++) {
			string id, name, a, owner; vector<string> posts; int followers;
		pages_file >> id;
		getline(pages_file,name,'1');
		//pages_file >> name;
		pages_file >> a;
			while (a != "-1") {
				posts.push_back(a);
				pages_file >> a;
			}
			pages_file >> owner; pages_file >> followers;
			
			pages_list.push_back(page(id, name, posts,owner,followers));
			
		}
	}
	void readPosts() {
		fstream posts_file("Posts.txt");
		posts_file >> post::total_posts;
		for (int i = 0; i < total_posts; i++) {
			string id, content, activ_content, a, owner;
			int date, month, likes, activ_number, hours, min,year;
			vector<string> comments;

			posts_file>>id;
			posts_file >> likes;
			posts_file >> year;
			posts_file >> month;
			posts_file >> date;
			posts_file >> hours;
			posts_file >> min;
			//posts_file.ignore(256, '\n');
			getline(posts_file, content, '1');
			getline(posts_file, activ_content,'1');
			if (activ_content != " ") {
				posts_file >> activ_number;
			}else
				activ_number = 0;
			//posts_file >> activ_content;
			//posts_file.ignore(256, '\n');
			posts_file >> owner;
			
			posts_file >> a;
			while (a != "-1") {
				comments.push_back(a);
				posts_file >> a;
			}

			posts_list.push_back(post(id, date, month, content, owner, likes, activ_number, activ_content, comments, hours, min, year));


		}
	}
	void readComments() {
		fstream comments_file("Comments.txt");
		comments_file >> comment::total_comments;
		for (int i = 0; i < total_comments; i++) {
			string id, owner_post, owner_user, content;
			comments_file >> id;
			comments_file >> owner_post;
			comments_file >> owner_user;
			getline(comments_file, content, '\n');

			comments_list.push_back(comment(id, owner_post, owner_user, content));
		}
	}
	
	string getUserName(string id) {
		int count = 0;
		for (auto& i : users_list) {
			if (id == i.getId()) {
				count++;
				return i.getName();
			}
		}
		if (count == 0) {
			return "user not found err";
		}
	}
	string getPageName(string id) {
	int count = 0;
	for (auto& i : pages_list) {
		if (id == i.getId()) {
			count++;
			return i.getName();
		}
	}
	if (count == 0) {
	return "page not found err";
	}
	}
	int UserAuth() {

		cout << "Enter Your Username or Id:				-1 to exit \n";
		string id; cin >> id;
		int a = 0; int c = 0; bool condition=true;
		while (condition) {
			c = 0;
			for (auto& i : users_list) {
				a++;
				if (i.getId() == id || i.getName() == id) {
					
					c++;
					break;
				}
			}

			if (id == "-1") {
				c = -1;
			}
			switch (c) {
			case 0:
				cout << "User Not Found" << endl;
				return 0;
				break;
			case 1:
				cout << "Logged in Successfully" << endl;
				cout << "Welcome " << users_list[a-1].getName() << endl;
				
				return a;
				break;
			case -1:
				return -1;
			default:
				cout << "Unexpected Error!" << endl;
				return 0;
				break;
			}
		}
	}
	bool DateAuthHome(post i) {
		time_t now = time(0);
		struct tm ltm;
		localtime_s(&ltm, &now); // Corrected usage of localtime_s
		int date = ltm.tm_mday;int month=ltm.tm_mon + 1; int year=ltm.tm_year + 1900;
		
		if (year == i.getYear() && month == i.getMonth() && (date == i.getDate()) || (date-1== i.getDate() )) {
			return true;
		}
		else 
			return false;



	}
	void MakeHome(int userno) {
		int userNo = userno - 1;
		vector<string> friends = users_list[userNo].getFriends();
		vector<page> followed_pages;
		for (auto& j : pages_list) {
			for (auto& k : users_list[userNo].getPages()) {
				if (j.getId() == k) {
					followed_pages.push_back(j);
				}
			}

		}


		for (auto& i : posts_list) {
			if (DateAuthHome(i)) {
				for (auto& j : friends) {

					if (j == i.getOwner() ) {
						home_posts.push_back(i);
					}
				
				}
				for (auto& j: followed_pages) {
					for (auto& k : j.getPosts()) {
						if (i.getId() == k) {
							home_posts.push_back(i);
						}
					}

				}
			}
		}



	}
	string getPostUser(string id) {
		int count = 0;
		for (auto& i : posts_list) {
			if (id == i.getId()) {
				count++;
				return i.getOwner();
			}
		}
		if (count == 0) {
			return "user not found err";
		}
	}
	void getName(string id,int userno,bool &isPage, string &ownername, string &pagename ) {
		// is this post of our friend?
		 
		for (auto& i: users_list[userno].getFriends()) {
			if (id == i) {
				// is our friend
				ownername = i;
				isPage = false;
				return;
				
			}
		}

		// must be a page we follows post
		vector<page> followed_pages;
		for (auto& j : pages_list) {
			for (auto& k : users_list[userno].getPages()) {
				if (j.getId() == k) {
					followed_pages.push_back(j);
				}
			}

		}
		for (auto& j : followed_pages) {
			for (auto& k : j.getPosts()) {
				string ownerpost = getPostUser(k);
				if (id == ownerpost) {
					pagename = j.getName();
					ownername = getUserName(ownerpost);
					isPage = true;
					return;
				}

			}
		}
		

	}
	
	
	void AddCommentToFile() {
		fstream comments_file("Comments.txt", ios::app);
		comments_file.seekp(0, ios::end);
		int size = comments_list.size();
		comments_file << comments_list[size-1].getId()<<" "<< comments_list[size-1].getOwnerPost() << " " << comments_list[size-1].getOwnerUser() << " " << comments_list[size-1].getContent() << endl;

	}
	void printHome(int userno) {
		
		cout << "================================================================================================================\n";
		cout<<"	\t\t\t\tHome Page \n";
		cout << "================================================================================================================\n";
		cout << "User: "<<users_list[userno].getName() << endl;
		cout << "\t\tThese are the latest Posts in your feed: \n\n";
		if (home_posts.size()==0) {
			cout << "\n\tnothing in your feed follow more pages\n";
		}
		else {
			for (auto& i : home_posts) {
				bool isFromPage=false;
				activ* a = i.getActivity();
				string pagename,ownername; int c = 0;
				getName(i.getOwner(), userno, isFromPage, ownername, pagename);
				
				if (!isFromPage) {
					cout << "\n\nPost id: " << i.getId() << "\t\t\t\t Dated : " << i.getDate() << "/" << i.getMonth() << "/" << i.getYear() << "\n\nYour Friend " << ownername << " said: \t\t " << i.getContent() << "\t\tlikes: " << i.getLikes() << "\n " << a->getContent() << " " << a->getNumber() << " \n\n comments : \n";

				}else
				cout <<"\n\nPost id: " << i.getId() << "\t\t\t\t Dated : " << i.getDate() << "/" << i.getMonth() << "/" << i.getYear() << "\n\n posted by " <<ownername<<" on "<< pagename << "  :  " << i.getContent() << "\t\tlikes: " << i.getLikes() << "\n " << a->getContent() << " " << a->getNumber() << " \n\n comments : \n";
				
				for (auto & j: comments_list) {
					if (j.getOwnerPost() == i.getId()) {

						//get owner name
						string name =getUserName(j.getOwnerUser());
						cout<<name<<" commented :\t "<<j.getContent()<<"\n\n";

					}
				}
				
			}

		}
		cout << "Add Comment? \n"; string choice; cin >> choice;
		if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y") {
			
				cout << "Enter comment: \n";
				cin.ignore();
				string content; getline(cin, content);
				cout << "Enter post id: \t"; 
				string id; 
				getline(cin, id);
				comments_list.push_back(comment("c"+to_string(comments_list.size()+1),id,users_list[userno].getId(),content));
				
				
				AddCommentToFile();
		}
		else {
			system("cls");
			MainMenu(userno);
		}
		
	
	}
	void Explore(int userno) {
		cout << "Explore Other Pages!!\n\n";
		for (auto& i : pages_list) {
			cout << i.getName() << "\t" ;
			
		}
		system("cls");
		void MainMenu(int userN0);

	}

	void ViewProfile(int userno) {
		
		for (int i = 0; i < 10; i++) { cout << "="; }
		cout << "\n";
		cout << "User: " << users_list[userno].getName() << endl;
		cout << "Id: " << users_list[userno].getId() << endl << endl;
		cout << "Friends list: \n";
		for (auto& i : users_list[userno].getFriends()) {cout<<getUserName(i)<<"\n";}
		cout << "\nFollowed Pages list: \n";
		for (auto& i : users_list[userno].getPages()) {cout << getPageName(i) << "\n"; }
		system("cls");
		void MainMenu(int userN0);

	}

		void MainMenu(int userN0) {
	
				cout<<"\t\tSelect an option: \n 1. Go Home \n 2. Explore \n 3. View Profile \n 4. Share Memories  \n 5. View Followed Pages \n 6. View Friends \n any another to exit\n";

				int a; cin >> a;
				switch (a)
				{
				case 1:
					printHome(userN0);
					break;
				case 2:
					Explore(userN0);
					break;
				case 3:
					ViewProfile(userN0);
				default:
					exit;
				}
				





		}
		void StartApp() {
			cout << "================================================================================================================";
			cout << "	\t\t\t\t\tWELCOME TO OOP PROJECT" << endl;
			cout << "================================================================================================================\n";
			int userN0 = UserAuth();
			if (userN0 == -1) {
			cout << "Exiting!";
			}
			else if (userN0 == 0) {
			userN0 = UserAuth();
			}
		
			// Found user
			user u = users_list[userN0-1];
			userN0 = userN0 - 1;

			MakeHome(userN0);
			MainMenu(userN0);
		
			
		}
	// halo
	
 };


int main() {
	
	Runner r;
	
	r.readUsers();
	r.readPages();
	r.readPosts();
	r.readComments();
	r.StartApp();
//hehehe
}