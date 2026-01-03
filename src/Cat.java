public abstract class Cat {
    protected int health;
    protected int speed;
    protected int power;

    public Cat(int h, int s, int p){
        this.health=h;
        this.speed=s;
        this.power=p;
    }
    protected void setStatistics(int h, int s, int p){
        this.health = h;
        this.speed = s;
        this.power = p;
    };

    public abstract String getPowerStatus();
    public abstract String getHealthStatus();
    public abstract String getSpeedStatus();
}