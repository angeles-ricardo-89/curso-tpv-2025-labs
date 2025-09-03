package com.priv.tpvsolutions.ndklab;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.priv.tpvsolutions.ndklab.databinding.ActivityMainBinding;

import android.content.Context;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'ndklab' library on application startup.
    static {
        System.loadLibrary("ndklab");
    }

    private ActivityMainBinding binding;

    private final ArrayList<Integer> integerList = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        EditText numberInput1 = binding.numberInput1;
        EditText numberInput2 = binding.numberInput2;
        TextView tvSum = binding.resultText;

        Button btnSum = binding.sumaButton;
        btnSum.setOnClickListener(v -> {
            try {
                int a = Integer.parseInt(numberInput1.getText().toString());
                int b = Integer.parseInt(numberInput2.getText().toString());
                int result = suma(a, b);
                tvSum.setText("Suma de " + a + " + " + b + " = " + result);
            } catch (NumberFormatException e) {
                tvSum.setText("Por favor ingresa números válidos");
            }
        });

        Button btnMultiply = binding.multiplyButton;
        btnMultiply.setOnClickListener(v -> {
            try {
                int a = Integer.parseInt(numberInput1.getText().toString());
                int b = Integer.parseInt(numberInput2.getText().toString());
                int result = multiply(a, b);
                tvSum.setText("Multiplicación de " + a + " * " + b + " = " + result);
            } catch (NumberFormatException e) {
                tvSum.setText("Por favor ingresa números válidos");
            }
        });

        Button btnDivid = binding.dividButton;
        btnDivid.setOnClickListener(v -> {
            try {
                int a = Integer.parseInt(numberInput1.getText().toString());
                int b = Integer.parseInt(numberInput2.getText().toString());
                if (b == 0) {
                    tvSum.setText("Error: No se puede dividir por cero");
                    return;
                }

                int result = divid(a, b);
                tvSum.setText("División de " + a + " / " + b + " = " + result);
            } catch (NumberFormatException e) {
                tvSum.setText("Por favor ingresa números válidos");
            }
        });

        // Integer List Manager UI
        EditText integerInput = binding.integerInput;
        LinearLayout numberListContainer = binding.numberListContainer;
        Button addNumberButton = binding.addNumberButton;
        Button clearListButton = binding.clearListButton;
        TextView sumText = binding.sumText;
        TextView multText = binding.multText;
        TextView divText = binding.divText;

        addNumberButton.setOnClickListener(v -> {
            String input = integerInput.getText().toString().trim();
            if (!input.isEmpty()) {
                try {
                    int value = Integer.parseInt(input);
                    integerList.add(value);
                    integerInput.setText("");
                    updateNumberListUI(numberListContainer, this);
                    updateOperatorsText(sumText, multText, divText);
                } catch (NumberFormatException ignored) {}
            }
        });

        clearListButton.setOnClickListener(v -> {
            integerList.clear();
            updateNumberListUI(numberListContainer, this);
            updateOperatorsText(sumText, multText, divText);
        });
    }

    private void updateNumberListUI(LinearLayout container, Context context) {
        container.removeAllViews();
        for (int num : integerList) {
            TextView tv = new TextView(context);
            tv.setText(String.valueOf(num));
            tv.setPadding(16, 8, 16, 8);
            tv.setTextSize(16);
            container.addView(tv);
        }
    }

    private void updateOperatorsText(TextView sumText, TextView multText, TextView divText) {
        int sum = 0;
        sum = sumIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        sumText.setText("Sum: " + sum);

        int mult = 0;
        mult = multIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        multText.setText("Mult: " + mult);

        int div = 0;
        div = divIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        divText.setText("Div: " + div);
    }

    /**
     * A native method that is implemented by the 'ndklab' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int suma(int a, int b);
    public native  int multiply(int a, int b);
    public native  int divid(int a, int b);
    public native  int sumIntegerArrayList(int[] numbers);
    public native  int multIntegerArrayList(int[] numbers);
    public native  int divIntegerArrayList(int[] numbers);


}