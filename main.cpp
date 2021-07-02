#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
class Player
{
private:
    sf::Sprite shape;
    sf::Texture shapetex;
    int posx;
    int posy;
public:
    Player()
    {
        shapetex.loadFromFile("./png/anagemi.png");
        shape.setTexture(shapetex);
        shape.setPosition(posx,posy);
        shape.setScale(0.7,0.7);
        shape.setOrigin(shapetex.getSize().x/2,shapetex.getSize().y/2);
        
    }
    void setpos(sf::Event& event){
        if(event.type ==sf::Event::MouseMoved){
            posy=event.mouseMove.y;
            posx=event.mouseMove.x;
            
        }

    }
    void draw(sf::RenderWindow& window){
        window.draw(shape);
    }
    sf::FloatRect getglobal(){
        return shape.getGlobalBounds();
    }
};

class Lazer
{
private:
    sf::Sprite shape;
public:
    Lazer()
    {   
        shape.setScale(0.75,0.75);
    }
    void update(){
        shape.move(0,-5);
    }
    void setpos(int x,int y){
        x-=10;
        y-=25;
        shape.setPosition(x,y);
    }
    
    void draw(sf::RenderWindow& window){
        window.draw(shape);
    }
    void setsprite(sf::Sprite sp){
        shape=sp;
    }
    float getposy(){
        return shape.getPosition().y;
    }
    sf::FloatRect getglobal(){
        return shape.getGlobalBounds();
    }
};

class Enemy
{
private:
    sf::Sprite shape;
public:
    void update(){
        shape.move(0,2);
    }
    void setsprite(sf::Sprite sprite){
        shape = sprite;
        shape.setOrigin(sprite.getTexture()->getSize().x/2,sprite.getTexture()->getSize().y/2);
        shape.setScale(0.5,0.5);
        shape.rotate(180);
    }
    void spawnenemy(sf::RenderWindow& window,int texsize){
        shape.setPosition(rand()%(window.getSize().x-texsize)+ texsize,0);
    }
    void draw(sf::RenderWindow& window){
        window.draw(shape);
    }
    float getposy(){
        return shape.getPosition().y;
    }
    sf::FloatRect getglobal(){
        return shape.getGlobalBounds();
    }
};

class texmenager
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;
    public:
        sf::Sprite getsprite(){
            texture.loadFromFile("./png/mermi.png");
            sprite.setTexture(texture);
            return sprite;
        }
        sf::Sprite egetsprite(){
            texture.loadFromFile("./png/enemy.png");
            sprite.setTexture(texture);
            return sprite;
        }
};

int deletearr(Enemy arr[],int index,int size){
    int a =0;
    for(a=0;a<size;a++){
        if(a==index)
            break;
    }
    if (index < size) 
   { 
     size -= 1; 
     for (int j=index; j<size; j++) 
        arr[j] = arr[j+1]; 
   }
   return size;
}
int deletearr(Lazer arr[],int index,int size){
    int a =0;
    for(a=0;a<size;a++){
        if(a==index)
            break;
    }
    if (index < size) 
   { 
     size -= 1; 
     for (int j=index; j<size; j++) 
        arr[j] = arr[j+1]; 
   }
   return size;
}
int deletearr(sf::Sprite arr[],int size){
    size -= 1; 
    for (int j=size; j<size; j++) 
        arr[j] = arr[j+1];
   return size;
}

int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1150, 864), "Space Shooter",sf::Style::Default,settings);
    window.setFramerateLimit(60);
    int score = 0;
    int hp = 3;
    sf::Sprite bg,hparr[hp],bg2;
    sf::Texture bgtx,heart;
    if(!bgtx.loadFromFile("./png/space2.png") || !heart.loadFromFile("./png/heart.png")){
        return -1;
    }
    bg.setTexture(bgtx);
    //bg.scale(0.7,0.7);
    int pos =0;
    for(int i =0;i<hp;i++){
        hparr[i].setTexture(heart);
        hparr[i].setScale(0.035,0.035);
        hparr[i].setPosition(window.getSize().x*0.1+pos,0);
        pos+= 20;
        
    }
    
    
    sf::Font font;
    sf::Text txt,scr,gameover;
    if(!font.loadFromFile("nerko.ttf")){
        return -1;
    }
    txt.setFont(font);
    
    txt.setCharacterSize(50);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);
    scr = txt;
    scr.setPosition(window.getSize().x*0.75, 0);
    txt.setString(L"HP: ");

    gameover.setFont(font);
    gameover.setString("GAME OVER");
    gameover.setOrigin((gameover.getGlobalBounds().width+gameover.getGlobalBounds().left)/2,(gameover.getGlobalBounds().height+gameover.getGlobalBounds().top)/2);
    gameover.setPosition(window.getSize().x/2-150,window.getSize().y/2-120);
    gameover.setCharacterSize(100);
    //gameover.setPosition(0,0);
    gameover.setFillColor(sf::Color::Magenta);

    Lazer lazers[20];
    Enemy enemies[10];
    int lcount = 0,ecount = 0;
    float timer =0;
    texmenager emenage,lmenage;
    
    
    
    while (window.isOpen())
    {   
        if(hp == 0){
            sf::Event eventt;
            while(window.pollEvent(eventt)){
                if (eventt.type == sf::Event::Closed){
                    window.close();
                    return 0;
                } 
            }
            window.clear(sf::Color::Black);
            window.draw(gameover);
            window.display();
            continue;
        }
        Player player;
        Enemy enemy; 
        sf::Event event;
        std::string str= "SCORE: " + std::to_string(score);
        scr.setString(str);
        while (window.pollEvent(event))
        {
            Lazer lazer;
            
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    lazer.setsprite(lmenage.getsprite());
                    lazer.setpos(event.mouseButton.x,event.mouseButton.y);
                    lazers[lcount] = lazer; 
                    lcount++;
                }
            } 
            
            player.setpos(event);
        } 

        
        if(fmod(timer,30) == 0){
            enemy.setsprite(emenage.egetsprite());
            enemy.spawnenemy(window,emenage.egetsprite().getTexture()->getSize().x);
            enemies[ecount] = enemy;
            ecount++;
        }
        
        
        window.clear();
        window.draw(bg);
        window.draw(txt);
        window.draw(scr);
        for(int i =0;i<hp;i++){
            window.draw(hparr[i]);
        }
        
        for(int i = 0;i<lcount;i++){
            lazers[i].draw(window);
            if(lazers[i].getposy()<0){
                lcount = deletearr(lazers,i,lcount);
            }
            lazers[i].update();
        }
        for(int a = 0;a<ecount;a++){
            enemies[a].draw(window);
            if(enemies[a].getposy()>window.getSize().y || enemies[a].getglobal().intersects(player.getglobal())){
                ecount = deletearr(enemies,a,ecount);
                hp = deletearr(hparr,hp);
                score--;
            }
            for(int k=0;k<lcount;k++){
                if(enemies[a].getglobal().intersects(lazers[k].getglobal())){
                    ecount = deletearr(enemies,a,ecount);
                    lcount = deletearr(lazers,k,lcount);
                    score++;
                }
            }
            enemies[a].update();
        }


        
        player.draw(window);
        timer += 0.5f;
        window.display();
    }

    return 0;
}