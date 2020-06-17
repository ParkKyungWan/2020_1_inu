import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.RowSpec;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.script.ScriptEngine;


/*
 
  	swing // 사칙연산 계산기
  				
 							*/


public class ExSwing extends JFrame {

	ScriptEngineManager mgr = new ScriptEngineManager();
    ScriptEngine engine = mgr.getEngineByName("JavaScript");
    

	int max_width = 300;
	int max_height = 500;
	JLabel ing = new JLabel("",JLabel.RIGHT);
	JLabel result = new JLabel("0",JLabel.RIGHT);
	
	
	
	public ExSwing() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout( new BorderLayout() );
		
		JPanel panel = new JPanel();                      //결과와 과정이 나올 판넬입니다
		panel.setBackground(Color.WHITE);
		getContentPane().add(panel, BorderLayout.NORTH);
		panel.setLayout(new GridLayout(2,1));              //2x1
		
		
		ing.setForeground(Color.red);
		panel.add(ing);                         //과정이 나올 라벨		
		panel.add(result);						//결과가 나올 라벨
		
		JPanel buttons_p = new JPanel();                 //판넬을 하나 만들어 줍니다.
		getContentPane().add(buttons_p, BorderLayout.CENTER);
		buttons_p.setLayout(new GridLayout(4, 4, 2, 2)); // 4x4 로 버튼이 들어갈 것입니다.
		
		JButton[] buttons = new JButton[16];
		String[] contents = { 
				"7", "8", "9", "*",
				"4", "5", "6", "-",
				"1", "2", "3", "+",
				"0", "C", ".", "=" }; //버튼의 레이아웃입니당
		for(int i = 0 ; i < 16; i ++) {
			buttons[i] = new JButton(contents[i]);
			buttons[i].setBackground(Color.white);
			
			if ( i != 13 && i != 15) buttons[i].addMouseListener(new ButtonClicked());
			else if (i == 13) buttons[i].addMouseListener(new ClearClicked()); // c 를 누르면 초기화됩니다
			else buttons[i].addMouseListener(new EqualClicked()); // = 를 누르면 결과가 나옵니다
			
			buttons_p.add(buttons[i]);
		}
		
		//상단부 판넬
		
		setSize(200,300);
		setResizable(false);
		setVisible(true);

	}
	
	class ButtonClicked extends MouseAdapter{
		public void mousePressed(MouseEvent e) {
			JButton tmp = (JButton) e.getSource();
			ing.setText( ing.getText() + tmp.getText() );
		}

	}
	class EqualClicked extends MouseAdapter {
		public void mousePressed(MouseEvent e) {
			
			String process = ing.getText();
			
			try {
				result.setText( engine.eval(process).toString() );
				ing.setText("");
			} catch (ScriptException e1) {
				result.setText("올바른 수식이 아닙니다");
			}
			
			
		}

	}
	class ClearClicked extends MouseAdapter{
		public void mousePressed(MouseEvent e) {
			ing.setText("");
		}

	}
	public static void main(String[] args) {
		new ExSwing();
	}
}
