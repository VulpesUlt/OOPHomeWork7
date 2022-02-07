#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>

void getUInt(uint16_t& num)
{
	int16_t data;
	do
	{
		std::cin >> data;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl << "Invalid input, please try again: ";
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (std::cin.gcount() > 1)
		{
			std::cin.clear();
			std::cout << std::endl << "Invalid input, please try again: ";
			continue;
		}

		if (data < 0)
		{
			std::cin.clear();
			std::cout << std::endl << "Invalid input, please try again: ";
			continue;
		}

		break;
	} while (true);

	num = data;
}

bool confirm()
{
	char ch = 'a';
	std::cout << "(y / n): ";
	while (true)
	{
		std::cin.get(ch);

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (std::cin.gcount() > 1)
		{
			std::cin.clear();
			continue;
		}

		if (ch == 'y')
			return true;
		else if (ch == 'n')
			return false;
		else
			continue;
	}
}

class Card
{
private:
	enum class suit
	{
		SPADES,
		CLUBS,
		HEARTS,
		DIAMONDS
	};

	enum class rank
	{
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE,
	};

	suit m_suit;
	rank m_rank;
	bool m_faceUp;

public:

	Card(uint16_t suit, uint16_t rank) : m_faceUp(false)
	{
		switch (suit)
		{
		case 0:
			m_suit = suit::SPADES;
			break;
		case 1:
			m_suit = suit::CLUBS;
			break;
		case 2:
			m_suit = suit::HEARTS;
			break;
		case 3:
			m_suit = suit::DIAMONDS;
			break;
		default:
			break;
		}

		switch (rank)
		{
		case 0:
			m_rank = rank::ACE;
			break;
		case 1:
			m_rank = rank::TWO;
			break;
		case 2:
			m_rank = rank::THREE;
			break;
		case 3:
			m_rank = rank::FOUR;
			break;
		case 4:
			m_rank = rank::FIVE;
			break;
		case 5:
			m_rank = rank::SIX;
			break;
		case 6:
			m_rank = rank::SEVEN;
			break;
		case 7:
			m_rank = rank::EIGHT;
			break;
		case 8:
			m_rank = rank::NINE;
			break;
		case 9:
			m_rank = rank::TEN;
			break;
		case 10:
			m_rank = rank::JACK;
			break;
		case 11:
			m_rank = rank::QUEEN;
			break;
		case 12:
			m_rank = rank::KING;
			break;
		default:
			break;
		}
	}

	bool Flip() // returnes true if card was fliped
	{
		if (m_faceUp)
			return false;
		else
		{
			m_faceUp = true;
			return true;
		}
	}

	uint32_t GetValue() const
	{
		switch (m_rank)
		{
		case Card::rank::TWO:
			return 2;
		case Card::rank::THREE:
			return 3;
		case Card::rank::FOUR:
			return 4;
		case Card::rank::FIVE:
			return 5;
		case Card::rank::SIX:
			return 6;;
		case Card::rank::SEVEN:
			return 7;
		case Card::rank::EIGHT:
			return 8;
		case Card::rank::NINE:
			return 9;
		case Card::rank::TEN:
			return 10;
		case Card::rank::JACK:
			return 10;
		case Card::rank::QUEEN:
			return 10;
		case Card::rank::KING:
			return 10;
		case Card::rank::ACE:
			return 1;
		default:
			return 0;
		}
	}

	friend std::ostream& operator<< (std::ostream&, Card&);
};

std::ostream& operator << (std::ostream& stream, Card& card)
{
	std::string suit;
	switch (card.m_suit)
	{
	case Card::suit::SPADES:
		suit = "Spades";
		break;
	case Card::suit::CLUBS:
		suit = "Clubs";
		break;
	case Card::suit::HEARTS:
		suit = "Hearts";
		break;
	case Card::suit::DIAMONDS:
		suit = "Diamonds";
		break;
	}
	std::string rank;
	switch (card.m_rank)
	{
	case Card::rank::TWO:
		rank = "2";
		break;
	case Card::rank::THREE:
		rank = "3";
		break;
	case Card::rank::FOUR:
		rank = "4";
		break;
	case Card::rank::FIVE:
		rank = "5";
		break;
	case Card::rank::SIX:
		rank = "6";
		break;
	case Card::rank::SEVEN:
		rank = "7";
		break;
	case Card::rank::EIGHT:
		rank = "8";
		break;
	case Card::rank::NINE:
		rank = "9";
		break;
	case Card::rank::TEN:
		rank = "10";
		break;
	case Card::rank::JACK:
		rank = "Jack";
		break;
	case Card::rank::QUEEN:
		rank = "Queen";
		break;
	case Card::rank::KING:
		rank = "King";
		break;
	case Card::rank::ACE:
		rank = "Ace";
		break;
	default:
		rank = "None";
	}
	if (card.m_faceUp)
		stream << rank << " " << suit << " |";
	else
		stream << "XX";
	return stream;
}

class Hand
{
protected:
	mutable std::vector<std::shared_ptr<Card>> m_collection;

public:
	void Add(std::shared_ptr<Card> newCard) { m_collection.push_back(newCard); }

	void Clear() { m_collection.clear(); }

	uint32_t GetValue() const
	{
		std::vector<std::shared_ptr<Card>>::iterator it = m_collection.begin();
		uint32_t result = 0;
		while (it != m_collection.end())
		{
			if ((*it)->GetValue() != 1)
				result += (*it)->GetValue();
			else
				result += ((result + (*it)->GetValue()) > 21) ? 1 : 11; // 1 or 11 points for aces
			it++;
		}
		return result;
	}

	bool Flip() // flipes next card in hand
	{
		std::vector<std::shared_ptr<Card>>::iterator it = m_collection.begin();
		while (it != m_collection.end())
		{
			if ((*it)->Flip()) { return true; };
			it++;
		}
		return false;
	}

	friend std::ostream& operator<< (std::ostream&, Hand&);
};

std::ostream& operator<< (std::ostream& stream, Hand& hand)
{
	std::vector<std::shared_ptr<Card>>::iterator it = hand.m_collection.begin();
	while (it != hand.m_collection.end())
	{
		stream << **it << "  ";
		it++;

	}
	return stream;
}

class GenericPlayer : public Hand
{
private:
	std::string name;
public:

	GenericPlayer(std::string name) : name(name) { }

	virtual bool IsHitting() const = 0;

	bool IsBoosted()
	{
		if (GetValue() > 21)
			return true;
		else
			return false;
	}

	std::string Bust()
	{
		return IsBoosted() ? " - boosted" : "";
	}

	std::string GetName() const { return name; }
};

class Player : public GenericPlayer
{
public:
	Player(std::string name) : GenericPlayer(name) { }

	virtual bool IsHitting() const override
	{
		std::cout << GenericPlayer::GetName() << ", do you need one more card? : ";
		return confirm();
	}

	void Win() const
	{
		std::cout << "Player " << GenericPlayer::GetName() << " won!" << " Total points: " << GetValue() << std::endl;
	}

	void Lose() const
	{
		std::cout << "Player " << GenericPlayer::GetName() << " lost" << " Total points: " << GetValue() << std::endl;
	}

	void Push() const
	{
		std::cout << "Player " << GenericPlayer::GetName() << " gets push" << " Total points: " << GetValue() << std::endl;
	}
};

class House : public GenericPlayer
{
public:
	House() : GenericPlayer("House") { }

	virtual bool IsHitting() const
	{
		if (GetValue() <= 16)
			return true;
		else
			return false;
	}

	void FlipFirstCard() { Flip(); }

	void FlipAll() { while (Flip()){ } }
};

class Deck : public Hand
{
private:
	void Populate()
	{
		for(uint16_t i = 0; i < 4; i++)
			for (uint16_t j = 0; j < 13; j++)
			{
				Add(std::make_shared<Card>(i, j));
				//std::cout << "(" << static_cast<int>(i) << " " << static_cast<int>(j) << ")";
			}
	}

	void Shuffle()
	{
		std::mt19937 g;
		g.seed(time(NULL));
		std::shuffle(m_collection.begin(), m_collection.end(), g);
	}
public:
	Deck()
	{
		Populate();
		Shuffle();
	}

	void Deal(Hand& aHand)
	{
		aHand.Add(m_collection.back());
		m_collection.pop_back();
	}

	void AdditionalCards(GenericPlayer& aGenericPlayer)
	{
		while (aGenericPlayer.IsHitting())
		{
			Deal(aGenericPlayer);
			aGenericPlayer.Flip();
			std::cout << "Your deck now: " << aGenericPlayer << std::endl;
			if (aGenericPlayer.IsBoosted()) { break; }
		}
	
	}
};

class Game
{
private:
	Deck m_deck;
	House m_house;
	std::vector<std::shared_ptr<Player>> m_player;
public:
	Game(std::vector<std::string>& players)
	{
		std::vector<std::string>::iterator it = players.begin();
		while (it != players.end())
		{
			m_player.push_back(std::make_shared<Player>(*it));
			it++;
		}
	}

	void print() 
	{
		system("CLS");
		std::cout << "Vulpes BlackJack V1.0" << std::endl << std::endl;

		std::cout << "Card dealer: " << m_house << std::endl;
		std::vector<std::shared_ptr<Player>>::iterator it = m_player.begin();
		while (it != m_player.end())
		{
			std::cout << "Player(" << (**it).GetName() << "): " << (**it) << (**it).Bust() << std::endl;
			it++;
		}
	}
	
	void congrats()
	{
		system("CLS");
		std::cout << "Vulpes BlackJack V1.0" << std::endl << std::endl;

		std::cout << "Card dealer: " << m_house << "Total points: " << m_house.GetValue() << std::endl;

		std::vector<std::shared_ptr<Player>>::iterator it = m_player.begin();
		while (it != m_player.end())
		{
			if ((**it).IsBoosted() && m_house.IsBoosted())
				(**it).Push();
			else if ((**it).IsBoosted() && !m_house.IsBoosted())
				(**it).Lose();
			else if (!(**it).IsBoosted() && m_house.IsBoosted())
				(**it).Win();
			else
			{
				if ((**it).GetValue() > m_house.GetValue())
					(**it).Win();
				else if ((**it).GetValue() < m_house.GetValue())
					(**it).Lose();
				else
					(**it).Push();
			}
			it++;
		}
	}
	
	void play()
	{
		// first two dealers cards
		m_deck.Deal(m_house);
		m_deck.Deal(m_house);
		m_house.FlipFirstCard();

		// giving players first cards
		std::vector<std::shared_ptr<Player>>::iterator it = m_player.begin();
		while (it != m_player.end())
		{
			m_deck.Deal(**it);
			(**it).Flip();
			m_deck.Deal(**it);
			(**it).Flip();
			it++;
		}

		print();

		//Players get addtitional cards
		it = m_player.begin();
		while (it != m_player.end())
		{
			m_deck.AdditionalCards(**it);
			it++;
			print();
		}

		//dealer get additional cards
		m_deck.Deal(m_house);
		m_house.FlipAll();

		//result of the game
		congrats();
	}
};

int main()
{
	do
	{
		//std::vector<std::string> playersTest = { "Anton", "Vasily", "Mihail" };

		uint16_t nPlayers;
		std::cout << "Enter the number of players: ";
		getUInt(nPlayers);
		
		if(nPlayers > 0)
		{
			std::vector<std::string> playerList;
			for (uint16_t i = 0; i < nPlayers; i++)
			{
				std::cout << "Player " << static_cast<int>(i) + 1 << ", enter your name: ";
				std::string buf;
				std::cin >> buf;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				playerList.push_back(buf);
			}
			
			Game game(playerList);
			game.play();
			
			std::cout << "Do you want to play again? ";
		}
		else
		{
			std::cout << "Is any body out there? ";
			if (confirm())
				std::cout << "Who just said that?!" << std::endl;
			else
				std::cout << "Then who am i talkin to?" << std::endl;
			std::cout << "Restart session? ";
		}
		
	} while (confirm());

	return 0;
}