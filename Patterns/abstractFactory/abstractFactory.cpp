#include "abstractFactory.h"
using namespace AbstractFactory;

template <typename T>
Side<T>::Side(std::string sideGeo, T* side) {
	this->sideGeo = sideGeo;
	this->side = side;
}

Maze::Maze() {

}

void Maze::addRoom(Room* room) {
	this->rooms.push_back(room);
}

Wall::Wall() {

}

Room::Room(int n) {
	this->id = n;
}

void Room::setSide(std::string side, Wall* wall) {
	this->sides.push_back(new Side<Wall>(side, wall));
}

void Room::setSide(std::string side, Door* door) {
	this->doors.push_back(new Side<Door>(side, door));
}

Door::Door(Room* r1, Room* r2) {

}

DoorNeedingSpell::DoorNeedingSpell(Room* r1, Room* r2) {

}

MazeGame::MazeGame() {

}

Maze* MazeGame::createMaze(MazeFactory& factory) {
	Maze* maze = factory.makeMaze();
	Room* room1 = factory.makeRoom(1);
	Room* room2 = factory.makeRoom(2);
	Door* door = factory.makeDoor(room1, room2);
	
	maze->addRoom(room1);
	maze->addRoom(room2);

	room1->setSide("North", factory.makeWall());
	room1->setSide("East", door);
	room1->setSide("South", factory.makeWall());
	room1->setSide("West", factory.makeWall());

	room2->setSide("North", factory.makeWall());
	room2->setSide("East", factory.makeWall());
	room2->setSide("South", factory.makeWall());
	room2->setSide("West", door);

}

MazeFactory::MazeFactory() {
}

Maze* MazeFactory::makeMaze() const {
	return new Maze;
}

Room* MazeFactory::makeRoom(int n) const {
	return new Room(n);
}

Wall* MazeFactory::makeWall() const {
	return new Wall;
}

Door* MazeFactory::makeDoor(Room* r1, Room* r2) const {
	return new Door(r1, r2);
}