import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.awt.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;

import java.util.Calendar; //시간가져오기

public class java_final extends JFrame {

	static Container c;
	JLabel timeL = new JLabel("");
	static float[] exchanges = { (float) 1207.30, (float) 1, (float) 11.25, (float) 15.88, (float) 0.052 };
	static JLabel BeforeMoney = new JLabel("");
	static JLabel AfterMoney = new JLabel("");
	static float before_p = 0;
	static float after_p = 0;
	static JButton[] buttons_b;
	static JButton[] buttons_a;
	static JTextField HowMuch = new JTextField(30);
	static JLabel result = new JLabel("0");

	public java_final() {
		setTitle("환전");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		c = getContentPane();
		c.setLayout(new BorderLayout());

		setJMenuBar(showMenu());

		ShowCalander();

		showBUTTONS();

		showInput();

		setSize(750, 400);
		resizeable(false);
		setVisible(true);
	}

	private void resizeable(boolean b) {
		// TODO Auto-generated method stub

	}

	public static void ShowCalander() {

		JPanel timec = new JPanel(); // 날짜,시간 출력
		timec.setBackground(Color.WHITE);
		timec.setLayout(new GridLayout(2, 1));

		JLabel time_now = new JLabel();
		Calendar cal = Calendar.getInstance();
		int year = cal.get(Calendar.YEAR);
		int month = cal.get(Calendar.MONTH) + 1;
		int day = cal.get(Calendar.DAY_OF_MONTH);
		int dayOfWeek = cal.get(Calendar.DAY_OF_WEEK);
		int hour = cal.get(Calendar.HOUR);
		int hourOfDay = cal.get(Calendar.HOUR_OF_DAY);
		int ampm = cal.get(Calendar.AM_PM);
		int minute = cal.get(Calendar.MINUTE);
		int second = cal.get(Calendar.SECOND);

		time_now.setText(year + "/" + month + "/" + day + "/");
		switch (dayOfWeek) {
		case Calendar.SUNDAY:
			time_now.setText(time_now.getText() + "일요일");
			break;
		case Calendar.MONDAY:
			time_now.setText(time_now.getText() + "월요일");
			break;
		case Calendar.TUESDAY:
			time_now.setText(time_now.getText() + "화요일");
			break;
		case Calendar.WEDNESDAY:
			time_now.setText(time_now.getText() + "수요일");
			break;
		case Calendar.THURSDAY:
			time_now.setText(time_now.getText() + "목요일");
			break;
		case Calendar.FRIDAY:
			time_now.setText(time_now.getText() + "금요일");
			break;
		case Calendar.SATURDAY:
			time_now.setText(time_now.getText() + "토요일");
			break;
		}
		if (ampm == Calendar.AM)
			time_now.setText(time_now.getText() + " 오전");
		else
			time_now.setText(time_now.getText() + " 오후 ");
		time_now.setText(time_now.getText() + hour + "시 " + minute + "분 " + second + "초 "); // JLabel 만들기

		timec.add(time_now);

		c.add(timec, BorderLayout.NORTH);

	}

	public static void showBUTTONS() {

		JPanel ExchangeP = new JPanel(); // 버튼 5개 들어갈 판넬
		ExchangeP.setBackground(Color.WHITE);
		ExchangeP.setLayout(new GridLayout(7, 2));

		JLabel lb = new JLabel("무엇을");
		ExchangeP.add(lb);
		JLabel la = new JLabel("무엇으로");
		ExchangeP.add(la);

		BeforeMoney.setForeground(Color.gray);
		ExchangeP.add(BeforeMoney);
		AfterMoney.setForeground(Color.green);
		ExchangeP.add(AfterMoney);

		buttons_b = new JButton[5];
		buttons_b[0] = new JButton("(미국) 달러");
		buttons_b[1] = new JButton("(한국) 원");
		buttons_b[2] = new JButton("(일본) 엔");
		buttons_b[3] = new JButton("(인도) 루피");
		buttons_b[4] = new JButton("(베트남) 동");

		buttons_a = new JButton[5];
		buttons_a[0] = new JButton("(미국) 달러");
		buttons_a[1] = new JButton("(한국) 원");
		buttons_a[2] = new JButton("(일본) 엔");
		buttons_a[3] = new JButton("(인도) 루피");
		buttons_a[4] = new JButton("(베트남) 동");

		for (int i = 0; i < 5; i++) {

			buttons_b[i].addMouseListener(new ButtonClicked(exchanges[i], true, i));
			ExchangeP.add(buttons_b[i]);

			buttons_a[i].addMouseListener(new ButtonClicked(exchanges[i], false, i));
			ExchangeP.add(buttons_a[i]);
		}

		c.add(ExchangeP, BorderLayout.WEST);

	}

	public static class ButtonClicked extends MouseAdapter {

		float point;
		boolean isBefore;
		int index;

		public ButtonClicked(float point, boolean isBefore, int index) {
			super();
			this.point = point;
			this.isBefore = isBefore;
			this.index = index;
		}

		public void mousePressed(MouseEvent e) {
			JButton tmp = (JButton) e.getSource();
			if (isBefore) {
				BeforeMoney.setText(" " + tmp.getText() + " ");
				before_p = this.point;

				for (int i = 0; i < 5; i++) {
					buttons_a[i].setVisible(true);
				}
				buttons_a[index].setVisible(false);

			} else {
				AfterMoney.setText("  " + tmp.getText());
				after_p = this.point;

				for (int i = 0; i < 5; i++) {
					buttons_b[i].setVisible(true);
				}
				buttons_b[index].setVisible(false);
			}
		}

	}

	public static void showInput() {
		JPanel inputs = new JPanel();// 버튼 5개 들어갈 판넬
		inputs.setBackground(Color.white);
		inputs.setLayout(new GridLayout(10, 1));

		JLabel lb = new JLabel("얼마를");
		inputs.add(lb);
		inputs.add(HowMuch);
		JButton cal = new JButton("계산하기");
		cal.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				float input_money = Float.parseFloat(HowMuch.getText());
				result.setText(input_money * (before_p / after_p) + " " + AfterMoney.getText());

				InputStreamReader in = null;
				FileInputStream fin = null;
				String log = "";
				try {
					fin = new FileInputStream("C:\\Users\\박경완\\Desktop\\log.txt");
					in = new InputStreamReader(fin, "MS949");
					int ch;
					while ((ch = in.read()) != -1) {
						System.out.print(ch);
						log += (char)ch;
					}
					System.out.println(log);
					in.close();
					fin.close();
				} catch (IOException except) {System.out.println("없");}
				
				FileWriter fout;
				try {
					fout = new FileWriter("C:\\Users\\박경완\\Desktop\\log.txt");
					fout.write(log+"\n"+BeforeMoney.getText()+" -> "+AfterMoney.getText()+"\n"+" "+input_money * (before_p / after_p) + " " + AfterMoney.getText()+"\n"); 
					fout.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				} 

			}
		});
		inputs.add(cal);
		JLabel lb2 = new JLabel("계산 결과: ");
		inputs.add(lb2);
		inputs.add(result);

		c.add(inputs, BorderLayout.CENTER);

	}

	public static JMenuBar showMenu() {
		JMenuBar mb = new JMenuBar();
		JMenu exit = new JMenu("프로그램 종료");
		exit.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				int result = JOptionPane.showConfirmDialog(null, "프로그램을 종료합니다", "Confirm", JOptionPane.YES_NO_OPTION);
				if (result == JOptionPane.YES_OPTION)
					System.exit(0);

			}
		});
		JMenu te = new JMenu("오늘의 환전");

		mb.add(exit);
		mb.add(te);

		return mb;
	}

	public static void main(String[] args) {
		new java_final();
	}

}
