import java.util.ArrayList;

public class BurgerJoint{
	static ArrayList<Burger> buffer = new ArrayList<Burger>();
	static int bufferBounds = 10;
	static int producer = 0;
	static int consumer = 0;
	static int maxNumber = 50;
	
	public static class Burger{
		public Burger(){};
	}

	public static class Producer extends Thread{
		boolean maxMade = false;
		public void run(){
			System.out.println("ProducerStarting");
			while(producer < maxNumber){
				if(buffer.size() <= bufferBounds){
					maxMade = false;
					Burger newBurger = new Burger();
					System.out.println("Making a Burger: " + producer);
					buffer.add(b);
					producer = producer + 1;
				}
				else{
					if(!maxMade){
						System.out.println("Max Burgers Made");
					}
					maxMade = true;
				}
			}
		}
	}
	
	public static class Consumer extends Thread{
		boolean noBurgers = true;
		public void run(){
			System.out.println("ConsumerStarting");
			while(consumer < maxNumber){
				if(buffer.size() != 0){
					noBurgers = false;
					System.out.println("Eating Burger: " + consumer);
					buffer.remove(0);
					consumer = consumer + 1;
				}
				else{
					if(!noBurgers){
						System.out.println("No Burgers To Eat");
					}
					noBurgers = true;
				}
			}
		}
	}
	public static void main(String[] args){
		Producer producer = new Producer();
		Consumer consumer = new Consumer();
		producer.start();
		consumer.start();
	}
}