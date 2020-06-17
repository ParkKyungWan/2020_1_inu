import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Calendar;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;


public class java_final extends JFrame {

	static Container c; //기반이 될 컨테이너 입니다.
	static JButton[] buttons; // 클릭할 버튼들입니다 ( line153 )
	static int[] costs = {4500,5000,18000,3000,5500};// 클릭할 버튼들입니다 ( 0~5번 메뉴에 대한 가격정보입니다. )
	static JTextField HowMuch = new JTextField(30); //textfield 입니다. 얼마나 살지 입력하는 곳입니다.
	static int now_clicked = 0; // 지금 선택된 메뉴의 index입니다.
	static int now_amount = 1; // HowMuch에 입력된 입력된 양입니다.
	static JButton cal = new JButton("추가하기"); //양을 입력한 후에 누를 버튼입니다.
	static JCheckBox to = new JCheckBox("포장하시려면 체크하세요"); //포장여부 확인
	static JLabel total = new JLabel(""); //편의를 위해 보여주는 현황입니다.ex) 짜장면 1개 && 짬뽕 2개 && 탕수 ... ... 
	static String[] bill = {"없음", "0", "0", "0"}; //영수증 출력을 입력하였을때 출력할 부분입니다.
	
	public java_final() {

		setTitle("음식 주문"); 
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		c = getContentPane();
		c.setLayout(new BorderLayout());

		setJMenuBar(showMenu()); //메뉴바 정하기
		ShowCalander(); //시간 보이기
		showBUTTONS(); //메뉴 선택버튼 보이기
		showInput();//주문량 선택하기
		showCosts();//가격표
		
		setSize(750, 400);
		setResizable(false);
		setVisible(true);
	}
	public static JMenuBar showMenu() {
		JMenuBar mb = new JMenuBar();
		JMenu exit = new JMenu("프로그램 종료");
		exit.addMouseListener(new MouseAdapter() {       //종료버튼을 누르면, 정말 종료할것인지 물어보고 종료합니다.
			public void mouseClicked(MouseEvent e) {
				int result = JOptionPane.showConfirmDialog(null, "프로그램을 종료합니다", "Confirm", JOptionPane.YES_NO_OPTION);
				if (result == JOptionPane.YES_OPTION)
					System.exit(0);

			}
		});
		JMenu te = new JMenu("영수증 출력");
		te.addMouseListener(new MouseAdapter() {        //영수증 출력을 누르면, bill[] 배열에서 값을 불러와 출력합니다.
			public void mouseClicked(MouseEvent e) {
				JDialog dialog = new JDialog();
				dialog.setTitle("주문 현황");
				dialog.setLayout(new GridLayout(4,1));
				dialog.add(new JLabel("마지막 주문 메뉴 : "+ bill[0]));
				dialog.add(new JLabel("개수 : "+ bill[1]));
				dialog.add(new JLabel("부분 합계 : "+ bill[2]));
				dialog.add(new JLabel("총 금액 : "+ bill[3]));
				dialog.setSize(200,300);
				dialog.setVisible(true);
			}
			
		});

		mb.add(exit);
		mb.add(te);

		return mb;
	}
	
	public static void ShowCalander() {

		JPanel timec = new JPanel(); // 날짜,시간 출력
		timec.setBackground(Color.WHITE);
		timec.setLayout(new GridLayout(1, 1));

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

		c.add(timec, BorderLayout.NORTH);      //북쪽에 추가합니다.

	}
	public static void showBUTTONS() {

		JPanel board = new JPanel(); // 버튼 5개 들어갈 판넬
		board.setBackground(Color.WHITE);
		board.setLayout(new GridLayout(6, 1));

		JLabel lb = new JLabel("메뉴판");
		board.add(lb);


		buttons = new JButton[5];
		buttons[0] = new JButton("짜장면");
		buttons[1] = new JButton("짬뽕");
		buttons[2] = new JButton("탕수육");
		buttons[3] = new JButton("군만두");
		buttons[4] = new JButton("볶음밥");


		for (int i = 0; i < 5; i++) {

			buttons[i].addMouseListener(new ButtonClicked(i));     //버튼을 눌렀을때 실행될 리스너 연결
			board.add(buttons[i]);

		}

		c.add(board, BorderLayout.WEST);

	}
	public static class ButtonClicked extends MouseAdapter {

		int index;
		
		public ButtonClicked(int index) {      //index를 같이 넣어줍니다. buttons[index] 로 눌린 버튼을 알 수 있습니다.
			super();                          //MouseAdapter 를 상속했으므로, 상위 객체의 생성자도 실행해줍니다.
			this.index = index;
		}
		public void mousePressed(MouseEvent e) {
			JButton tmp = (JButton) e.getSource();   //눌린 버튼을 담아옵니다.
			now_clicked = index;                      //지금 선택된 음식의 index 를 기록합니다.
			
			HowMuch.setEnabled(true);              // *** 음식이 선택되면 입력창 활성화 ***
			cal.setEnabled(true);
			to.setEnabled(true);

			
			cal.setText("추가하기 ("+tmp.getText()+")"); //어떤 음식이 선택되어있는지 알려줌
			
			
		}

	}
	
	public static void showInput() {
		JPanel inputs = new JPanel();// 버튼 5개 들어갈 판넬
		inputs.setBackground(Color.white);
		inputs.setLayout(new GridLayout(10, 1));

		JLabel lb = new JLabel("얼마나 사실건가요?");
		inputs.add(lb);
		
		HowMuch.setEnabled(false);     //*** 음식이 선택되기 전까지 입력 부분 비활성화 *** 
		inputs.add(HowMuch);
		
		to.setEnabled(false);
		inputs.add(to);
		
		cal.setEnabled(false);
		cal.addMouseListener(new order());
		inputs.add(cal);
		
		inputs.add(total);
		

		c.add(inputs, BorderLayout.CENTER);

	}
	public static class order extends MouseAdapter {


		public void mousePressed(MouseEvent e) {
			if (!HowMuch.getText().equals("")) {        //무언가 입력되어 있을 때만 amount 값을 받아옵니다.
													 //공백이면 기본값인 1이 됩니다.
				now_amount = Integer.parseInt(HowMuch.getText());
				
				
			}

			String newText = total.getText()+"  "+buttons[now_clicked].getText();
			newText += " "+now_amount+ "개";
			if(to.isSelected()) newText+=" (포장) ";
			
			newText += " && ";
			total.setText( newText);
			
			HowMuch.setEnabled(false);
			cal.setEnabled(false);
			to.setEnabled(false);                      //*** 음식이 선택되기 전까지 입력 부분 비활성화 *** 
			buttons[now_clicked].setVisible(false);
			
			bill[0] = buttons[now_clicked].getText();             //bill ( 주문정보 (영수증 ) ) 설정
			bill[1] = Integer.toString(now_amount);
			bill[2] = Integer.toString(costs[now_clicked]*now_amount);
			bill[3] = Integer.toString( Integer.parseInt( bill[3]) + Integer.parseInt(bill[2]) );
			now_amount = 1;                    //다시 기본값으로 만들어주기
		
			cal.setText("추가하기");
			
			InputStreamReader in = null;           //파일 불러와서 저장
			FileInputStream fin = null;
			String log = "";
			try {
				fin = new FileInputStream("C:\\Users\\박경완\\Desktop\\log.txt");
				in = new InputStreamReader(fin, "MS949");
				int ch;
				while ((ch = in.read()) != -1) {
					log += (char)ch;
				}
				in.close();
				fin.close();
			} catch (IOException except) {System.out.println("존재하지 않습니다");}   //파일 not found 에러 ( 에러 뜨면 자동으로 생성해주는 것 같습니다)
			
			FileWriter fout;
			try {
				fout = new FileWriter("C:\\Users\\박경완\\Desktop\\log.txt");
				fout.write(log+"\n"+bill[0]+"을  "+bill[1]+"개 주문 "+bill[2]+"원을 추가."+"\n");  //기존 내용 + 추가된 내용으로 write
				fout.close();
			} catch (IOException e1) {
				e1.printStackTrace();
			} 
			
			ShowResult();
		}

		
	}
	
	public static void ShowResult() {  //추가하기 누르면 현황 (총 합계 ) 출력
		
		
		JDialog dialog = new JDialog();     
		dialog.setTitle("주문 현황");
		dialog.add(new JLabel("합계 : "+ bill[3]));
		dialog.setSize(200,100);
		dialog.setVisible(true);
	}
	public static void showCosts() {
		JPanel costs_p = new JPanel();// 버튼 5개 들어갈 판넬
		costs_p.setBackground(Color.white);
		costs_p.setLayout(new GridLayout(6, 1));
		
		JLabel lb = new JLabel("      <가격표 >         ");
		costs_p.add(lb);
		
		JLabel[] jb = new JLabel[5];
		
		for(int i = 0 ; i < 5 ; i ++) {
			jb[i] = new JLabel("    "+buttons[i].getText()+" : "+costs[i]+"    ");     
			costs_p.add(jb[i]);
		}
		

		c.add(costs_p, BorderLayout.EAST);//가격표 출력

	}
	public static void main(String[] args) {
		new java_final();
		
	}
}
