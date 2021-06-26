#pragma once
#include <vector>
#include <string>

/* Абстрактная фабрика
	Интерфейс, для создания семейств взаимоствязанных или взаимозависимых объектов, 
	не специфицируя их конкретных классов
	*/

// Пример: Лабиринт


namespace AbstractFactory{

	template <typename T>
	struct Side {
	private:
		std::string side;
		T* side;
	public:
		Side(std::string sideGeo, T* side);
	};

	class Maze {
	private:
		std::vector<Room*> rooms;
		int id = 0;
	public:
		Maze();
		void addRoom(Room* room);
	};

	class Wall {
	private:
		int id = 0;
	public:
		Wall();
	};

	class BombedWall : public Wall {
	private:
		int isExist = 0;
	public:
		BombedWall() : Wall() {

		}
	};

	class Room {
	private:
		int id = 0;
		std::vector<Side<Wall>*> sides;
		std::vector<Side<Door>*> doors;
	public:
		Room(int n);
		void setSide(std::string side, Wall* wall);
		void setSide(std::string side, Door* door);
	};

	class RoomWithBomb : public Room {
	private:
	public:
		RoomWithBomb(int n) : Room(n) {
		};
	};


	class Door {
	public:
		Door(Room* r1, Room* r2);
		int id = 0;
	};

	class DoorNeedingSpell {
	public:
		DoorNeedingSpell(Room* r1, Room* r2);
		int id = 0;
	};

	class MazeFactory {
	public:
		MazeFactory();

		virtual Maze* makeMaze() const;
		virtual Wall* makeWall() const;
		virtual Room* makeRoom(int n) const;
		virtual Door* makeDoor(Room* r1, Room* r2) const;
	};

	class EnchantedMazeFactory: public MazeFactory {
	public:
		EnchantedMazeFactory() {};

		virtual Room* MakeRoom(int n) const {
			//return new EnchantedRoom(n, CastSpell());
		}
		virtual Door* MakeDoor(Room* r1, Room* r2) const {
			//return new DoorNeedingSpell(r1, r2); 
		}
	protected:
		//Spell* CastSpell() const;
	};

	class BombedMazeFactory : public MazeFactory {
	public:
		BombedMazeFactory() {};

		virtual Room* MakeRoom(int n) const {
			//return new RoomWithBomb(n,);
		}
		virtual Wall* makeWall() const {
			//return new BombedWall(r1, r2);
		}
	};

	class MazeGame {
	public:
		MazeGame();
		Maze* createMaze(MazeFactory& factory);
	};


}