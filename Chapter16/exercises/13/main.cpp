#include <cstddef>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

std::default_random_engine& random_engine()
{
	static std::default_random_engine engine(
		std::chrono::steady_clock::now().time_since_epoch().count()
	);
	return engine;
}

template <typename T>
T random_integer(T min, T max)
{
	return std::uniform_int_distribution<T>{min, max}(random_engine());
}

struct Room
{
	Room(std::size_t room_number) :
		number{room_number}
	{}

	enum Kind
	{
		normal,
		bat,
		pit,
	};

	bool is_special() const
	{
		return kind != Kind::normal;
	}
	std::size_t neighbor_capacity() const
	{
		return neighbors.size();
	}
	std::size_t neighbor_count() const
	{
		return neighbor_capacity()
			- std::count(neighbors.cbegin(), neighbors.cend(), nullptr);
	}
	void add_neighbor(Room& neighbor)
	{
		neighbors[neighbor_count()] = &neighbor;
	}

	Kind kind{Kind::normal};
	std::size_t number;
	std::array<Room*, 3> neighbors{};
};

using Rooms = std::vector<Room>;

void connect_rooms(Room& a, Room& b)
{
	a.add_neighbor(b);
	b.add_neighbor(a);
}

void connect_rooms(Rooms& rooms)
{
	for (std::size_t i = 1; i < rooms.size(); ++i)
	{
		connect_rooms(rooms[i - 1], rooms[i]);
	}
	for (std::size_t i = 0; i < 4; ++i)
	{
		connect_rooms(rooms[i], rooms[7 + i * 2]);
		connect_rooms(rooms[rooms.size() - 4 + i], rooms[6 + i * 2]);
	}
	for (std::size_t i = 0; i < 2; ++i)
	{
		connect_rooms(rooms[i * 5], rooms[4 + i * 10]);
	}
	connect_rooms(rooms[15], rooms[19]);
}

void place_special_rooms(Rooms& rooms, std::size_t n, Room::Kind special)
{
	for (std::size_t cnt = 0; cnt < n; )
	{
		// first room is always empty!
		// that's where the player starts
		Room& room = rooms[random_integer<std::size_t>(1, rooms.size() - 1)];
		if (!room.is_special())
		{
			room.kind = special;
			++cnt;
		}
	}
}

void place_special_rooms(Rooms& rooms)
{
	constexpr std::size_t pit_count = 2;
	constexpr std::size_t bat_count = 2;
	place_special_rooms(rooms, pit_count, Room::pit);
	place_special_rooms(rooms, bat_count, Room::bat);
}

Rooms create_rooms()
{
	constexpr std::size_t room_count = 20;
	Rooms rooms;
	rooms.reserve(room_count);
	for (std::size_t i = 0; i < room_count; ++i)
	{
		rooms.emplace_back(i + 1);
	}
	connect_rooms(rooms);
	place_special_rooms(rooms);
	return rooms;
}

class HuntTheWumpus
{
	enum class GameState
	{
		in_progress,
		victory,
		defeat,
	};
public:
	HuntTheWumpus() : rooms{create_rooms()}
	{
		place_player();
		place_wumpus();
	}
	HuntTheWumpus(const HuntTheWumpus&) = delete;
	HuntTheWumpus& operator=(const HuntTheWumpus&) = delete;
	void play()
	{
		while (std::cin && state == GameState::in_progress)
		{
			print_status();
			std::cout << "Move or shoot? ";
			if (char cmd; std::cin >> cmd)
			{
				switch (cmd)
				{
					case 'm':
					{
						std::size_t next_room;
						if (std::cin >> next_room)
						{
							if (is_nearby([next_room](const Room* neighbor) {
								return next_room == neighbor->number;
							})) {
								move_to(next_room - 1);
							}
						}
						if (player_pos == wumpus_pos)
						{
							std::cout << "\nThe wumpus ate you!";
							state = GameState::defeat;
						}
						else if (player_pos->kind == Room::pit)
						{
							std::cout << "\nYou fell into a bottomless pit!";
							state = GameState::defeat;
						}
						else if (player_pos->kind == Room::bat)
						{
							std::cout << "\nA bat picked you up!\n";
							player_pos = &random_room(
								[this](const Room& room) {
									return room.number != player_pos->number
										&& room.number != wumpus_pos->number
										&& !room.is_special();
								}
							);
						}
						break;
					}
					case 's':
					{
						if (arrows == 0)
						{
							std::cout << "\nYou have no arrows!\n";
						}
						else
						{
							std::vector<std::size_t> arrowed_rooms;
							for (std::size_t i = 0; i < 3 && std::cin; ++i)
							{
								if (std::size_t room_number; std::cin >> room_number)
								{
									arrowed_rooms.push_back(room_number);
								}
								if (char delim; std::cin.get(delim) && delim != '-')
									break;
							}
							bool shoot_success = false;
							std::cout << '\n';
							for (std::size_t i = 0; i < arrowed_rooms.size() && state == GameState::in_progress; ++i)
							{
								std::size_t room_number = arrowed_rooms[i];
								if (room_number == 0 || room_number - 1 >= rooms.size())
								{
									std::cout << "Room " << room_number << " doesn't exist!\n";
									continue;
								}
								std::cout << "Shooting into room " << room_number << "...\n";
								shoot_success = true;
								const Room& room = rooms[room_number - 1];
								if (&room == player_pos)
								{
									std::cout << "\nYou've shot yourself!\n";
									state = GameState::defeat;
								}
								else if (&room == wumpus_pos)
								{
									std::cout << "\nYou've killed the wumpus!\n";
									state = GameState::victory;
								}
							}
							if (shoot_success && state == GameState::in_progress)
							{
								std::cout << "\nYou've awoken the wumpus!\n";
								wumpus_pos = wumpus_pos->neighbors[random_integer(0, 2)];
								--arrows;
								std::cout << '\n' << arrows << " arrows remaining!\n";
							}
						}
					}
				}
			}
			std::cout << '\n';
		}
	}
private:
	void move_to(std::size_t room_no)
	{
		player_pos = &rooms[room_no];
	}
	template <typename Pred>
	Room& random_room(Pred pred)
	{
		std::size_t i = 0;
		do
		{
			i = random_integer<std::size_t>(0, rooms.size() - 1);
		} while (!pred(rooms[i]));
		return rooms[i];
	}
	void place_player()
	{
		player_pos = &random_room([](const Room& room) {
			return !room.is_special();
		});
	}
	void place_wumpus()
	{
		wumpus_pos = &random_room([this](const Room& room) {
			return room.number != player_pos->number;
		});
	}
	template <typename Pred>
	bool is_nearby(Pred pred) const
	{
		return std::find_if(
			player_pos->neighbors.cbegin(),
			player_pos->neighbors.cend(),
			pred
		) != player_pos->neighbors.cend();
	}
	bool wumpus_nearby() const
	{
		return is_nearby([this](const Room* neighbor) {
			return neighbor == wumpus_pos;
		});
	}
	bool pit_nearby() const
	{
		return is_nearby([](const Room* neighbor) {
			return neighbor->kind == Room::pit;
		});
	}
	bool bat_nearby() const
	{
		return is_nearby([](const Room* neighbor) {
			return neighbor->kind == Room::bat;
		});
	}
	void print_nearby_hazard() const
	{
		if (wumpus_nearby())
			std::cout << "\tI smell the wumpus!\n";
		if (pit_nearby())
			std::cout << "\tI feel a breeze!\n";
		if (bat_nearby())
			std::cout << "\tI hear a bat!\n";
	}
	void print_nearby_rooms() const
	{
		std::cout << "Tunnels lead to";
		for (const Room* neighbor : player_pos->neighbors)
			std::cout << ' ' << neighbor->number << '.';
		std::cout << '\n';
	}
	void print_status() const
	{
		std::cout << "You are in room " << player_pos->number << ".\n";
		print_nearby_hazard();
		print_nearby_rooms();
	}
private:
	int arrows = 5;
	Rooms rooms;
	Room* player_pos;
	Room* wumpus_pos;
	GameState state{GameState::in_progress};
};

int main()
{
	HuntTheWumpus game;
	game.play();
}
