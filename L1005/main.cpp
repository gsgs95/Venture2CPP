// 2D World
// Character::Player/Monster
// Monster.Type = Slime, Boar, Goblin

#include <iostream>

#define SAFE_DELETE(A) if(A) { delete (A); (A) = nullptr;}

using namespace std;

enum class Direction
{
	EAST,
	WEST,
	SOUTH,
	NORTH,
};

enum class MonsterType
{
	SLIME,
	BOAR,
	GOBLIN,
};

struct FLocation
{
	int X;
	int Y;
};

class FWorld
{
public:
	FLocation Root;
	FLocation Size;
};

class FCharacter
{
public:
	FCharacter(FLocation Location = {0,0}, string Name = "Character", int HP = 0, int ATK = 10)
		: Name{ Name }, Location{ Location.X, Location.Y }, HP{ HP }, ATK{ ATK }
	{
		cout << "FCharacter()" << endl;
	}
	virtual ~FCharacter()
	{
		cout << "~FCharacter()" << endl;
	}
	virtual bool Move(Direction Dir, FWorld World)
	{
		bool CanMove = false;
		switch (Dir)
		{
		case Direction::EAST:
			if (Location.X < World.Size.X)
			{
				Location.X += 1;
				CanMove = true;
			}
			break;
		case Direction::WEST:
			if (Location.X > 0)
			{
				Location.X -= 1;
				CanMove = true;
			}
			break;
		case Direction::SOUTH:
			if (Location.Y < World.Size.Y)
			{
				Location.Y += 1;
				CanMove = true;
			}
			break;
		case Direction::NORTH:
			if (Location.Y > 0)
			{
				Location.Y -= 1;
				CanMove = true;
			}
			break;
		}
		return CanMove;
	}
	virtual void Attack(FCharacter& OtherCharacter)
	{
		cout << Name << " 의 공격!" << endl;
		OtherCharacter.DecreaseHP(ATK);
		OtherCharacter.PrintHP();
	}
	virtual void DecreaseHP(int Damage)
	{
		if (HP <= Damage)
		{
			HP = 0;
		}
		else
		{
			HP -= Damage;
		}
	}
	virtual void PrintHP()
	{
		cout << "[ "<< Name << "] HP : " << HP << endl;
	}
	virtual bool IsDead()
	{
		return (HP <= 0);
	}

	virtual void Dead()
	{
		cout << Name << " is dead..." << endl;
	}
	virtual void PrintInfo()
	{
		cout << ">>>>> [ " << Name << " ] <<<<<" << endl;
		cout << "Location : (" << Location.X << ", " << Location.Y << ")" << endl;
		cout << "HP : " << HP << endl;
		cout << "ATK : " << ATK << endl;
	}

protected:
	string Name;
	FLocation Location;
	int HP;
	int ATK;
};

class FPlayer : public FCharacter
{
public:
	FPlayer(FLocation Location = {0,0}, string Name = "Player 0", int HP = 100, int ATK = 10, int Coin = 0)
		: Coin { Coin }, FCharacter{ Location, Name, HP, ATK }
	{
		cout << "FPlayer()" << endl;

	}
	virtual ~FPlayer()
	{
		cout << "~FPlayer()" << endl;
	}
	void CollectCoin(const int Coin)
	{
		this->Coin += Coin;
		cout << "[" << Name << "] : Get " << Coin << " Coin";
		if (Coin != 1 && Coin != 0) cout << "s";
		cout << endl;
	}

	virtual void  Dead()
	{
		cout << "Player [ "<< Name << " ] is dead..." << endl;
	}

	virtual void PrintInfo()
	{
		FCharacter::PrintInfo();
		cout << "Coin : " << Coin << endl;
	}

protected: // ULocation Location, int HP
	int Coin;

public:
	static FPlayer* CreatePlayer(const string& Name)
	{
		FPlayer* Player = new FPlayer({ 0,0 }, Name);
		return Player;
	}
};

class FMonster : public FCharacter
{
public:
	FMonster(MonsterType Type = MonsterType::SLIME, FLocation Location = { 0,0 })
		: Type{ Type }, FCharacter{ Location }
	{
		switch (Type)
		{
		case MonsterType::SLIME:
			Name = "Slime";
			HP = 30;
			ATK = 3;
			break;
		case MonsterType::BOAR:
			Name = "Boar";
			HP = 100;
			ATK = 8;
			break;
		case MonsterType::GOBLIN:
			Name = "Goblin";
			HP = 80;
			ATK = 10;
			break;
		}
		cout << "FMonster()" << endl;
	}
	virtual ~FMonster()
	{
		cout << "~FMonster()" << endl;
	}

protected:
	MonsterType Type;
};

int main()
{
	cout << "Create Player" << endl;
	// 동적으로 할당해야 원할때 메모리 해제 가능.
	FPlayer* Player = new FPlayer{ { 1,2 }, "Player0" };
	// 다음과 같이 생성시 맘대로 메모리 해제 불가능
	// FPlayer P;

	cout << "\nCreate Monster" << endl;
	FMonster* AMonster = new FMonster{ MonsterType::BOAR };

	cout << endl;
	Player->PrintInfo();

	cout << "\nPlayer->Dead()" << endl;
	Player->Dead();
	Player = nullptr;
	
	cout << endl;
	AMonster->PrintInfo();

	cout << "\nMonster->Dead()" << endl;
	AMonster->Dead();
	AMonster = nullptr;

	// 원할때 메모리 해제
	cout << "\ncustom delete Player" << endl;
	SAFE_DELETE(Player);
	cout << "\ncustom delete Monster" << endl;
	SAFE_DELETE(AMonster);


	return 0;
}