// A simple auto-FRS program written in C++.
// UNTESTED, USE AT YOUR OWN RISK!

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cpr/cpr.h>

int main()
{
	std::ifstream config("config");
	if (!config.is_open()) {
		std::cout << "Config file not found!" << std::endl;
		getchar();
		return 0;
	}
	std::string nrp;
	std::string PHPSESSID;
	std::string temp;
	int try_count = 5;
	int timeout = 5;
	std::getline(config, nrp);
	std::getline(config, PHPSESSID);
	if (std::getline(config, temp))
		try_count = std::stoi(temp);
	if (std::getline(config, temp))
		timeout = std::stoi(temp);

	cpr::Session session;
	session.SetUrl("https://integra.its.ac.id/dashboard.php?sim=AKAD__10__");
	session.SetCookies(cpr::Cookies{ { "PHPSESSID", PHPSESSID } });

	auto r = session.Get();
	std::cout << r.url << std::endl;

	if (r.text.find("index.php") != std::string::npos)
		std::cout << "Invalid session ID!" << std::endl;
	else {
		std::string redirect = r.text.substr(r.text.find("https://akademik.its.ac.id/gate.php?s="));
		redirect.erase(redirect.end() - 2, redirect.end());

		session.SetUrl(redirect);
		r = session.Get();
		std::cout << r.url << std::endl;

		session.SetUrl("https://akademik.its.ac.id/list_frs.php");
		r = session.Get();
		std::cout << r.url << std::endl;
		std::cout << "NRP: " << nrp << std::endl;
		while (try_count--) {
			std::ifstream courses("courses");
			if (!courses.is_open()) {
				std::cout << "Courses file not found!" << std::endl;
				getchar();
				return 0;
			}
			std::cout << "Taking courses..." << std::endl;
			std::string course;
			while (std::getline(courses, course)) {
				session.SetPayload(cpr::Payload{ {"nrp",nrp},{"act","ambil"},{"key",course} });
				r = session.Post();
				std::cout << r.status_code << std::endl;
			}
			courses.close();
			std::this_thread::sleep_for(std::chrono::seconds(timeout));
		}
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
