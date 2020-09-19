//构造函数
    m_attacking(false),
    m_damage(10),//攻击力10
    m_fireRate(1000),//1000ms
    m_chooseEnemy(NULL),

    m_fireRateTime=new QTimer(this);
    connect(m_fireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));


//其他函数
Tower::~Tower()
{
    delete m_fireRateTime;
    m_fireRateTime=NULL;
    m_chooseEnemy=NULL;
    m_game=NULL;
    delete m_chooseEnemy;
}
void Tower::chooseEnemyFromAttack(Enemy *enemy)
{
    m_chooseEnemy=enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);//该敌人受到该防御塔的攻击
}

void Tower::attackEnemy()
{
    m_fireRateTime->start(m_fireRate);//开始攻击
}

void Tower::shootWeapon()
{
    Bullet * bullet=new Bullet(m_pos,m_chooseEnemy->getPos(),m_damage,m_chooseEnemy,m_game);//构造一个子弹，准备攻击敌人
    bullet->move();
    m_game->addBullet(bullet);//将该子弹添加到mainwindow中
}

void Tower::targetKilled()
{
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();//敌人死亡，停止开火
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->getLostSight(this);
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();
}

void Tower::checkEnemyInRange()
{
    if(m_chooseEnemy)//如果有了攻击的敌人
        {
            QVector2D normalized(m_chooseEnemy->getPos()-m_pos);
            normalized.normalize();
            if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->getPos(),1))//当敌人不在范围内的时候
            {
                lostSightOfEnemy();
            }
        }
        else//如果没有攻击的敌人，就遍历enemylist，找到在攻击范围内的敌人
        {
            QList<Enemy * > enemyList=m_game->getEnemyList();
            foreach(Enemy * enemy,enemyList)
                if(collisionWithCircle(m_pos,m_attackRange,enemy->getPos(),1))
                {
                    chooseEnemyFromAttack(enemy);
                    break;
                }
        }
}

Enemy * Tower::getAttackedEnemy()
{
    return m_chooseEnemy;
}
