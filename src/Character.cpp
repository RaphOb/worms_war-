#include "Character.hh"

double Character::getX() const {
    return m_x;
}

void Character::setX(double x) {
    this->m_x = x;
    this->NotifyAll();
}

double Character::getY() const {
    return m_y;
}

void Character::setY(double y) {
    this->m_y = y;
    this->NotifyAll();
}

int Character::getLife() const {
    return m_life;
}

void Character::setLife(int life) {
    this->m_life = life;
    this->NotifyAll();
}

void Character::draw(sf::RenderWindow& window) {

}

void Character::update(sf::Time frameTime) {

}



void Character::AddObserver(IObserver *obs) {
    if (obs != nullptr) {
        this->m_observers.emplace_back(obs);
    }
}

void Character::RemoveObserver(IObserver *obs) {
    if (obs != nullptr) {
        this->m_observers.remove(obs);
    }
}

void Character::NotifyAll() {
    for (IObserver *obs: this->m_observers) {
        obs->Notify(this);
    }
}

Character::Character() {
    this->m_life = 0;
    this->m_x = 0;
    this->m_y = 0;
}

std::string Character::Serialize() {
    std::string str;
    str.append("m_life:").append(std::to_string(this->m_life)).append(";");
    str.append("m_x:").append(std::to_string(this->m_x)).append(";");
    str.append("m_y:").append(std::to_string(this->m_y));
    return str;
}
