package com.priv.tpvsolutions.ndklab;

import android.content.Context;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.priv.tpvsolutions.ndklab.databinding.ActivityMainBinding;

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

        TextView tvSum = binding.resultText;
        Button btnSum = binding.sumaButton;
        Button btnMult = binding.multiplyButton;
        Button btnDivide = binding.divideButton;


        btnSum.setOnClickListener(v -> {
            int a = 5;
            int b = 3;
            int result = suma(a, b);
            tvSum.setText("Suma de " + a + " + " + b + " = " + result);
        });

        btnMult.setOnClickListener(v -> {
            int a = 10;
            int b = 2;
            int result = multiply(a, b);
            tvSum.setText("Multiplicación de " + a + " * " + b + " = " + result);
        });

        btnDivide.setOnClickListener(v -> {
            int a = 10;
            int b = 2;
            int result = divide(a, b);
            tvSum.setText("División de " + a + " / " + b + " = " + result);
        });

        // Integer List Manager UI
        EditText integerInput = binding.integerInput;
        LinearLayout numberListContainer = binding.numberListContainer;
        Button addNumberButton = binding.addNumberButton;
        Button multiplyNumberButton = binding.multiplyNumberButton;
        Button divideNumberButton = binding.divideNumberButton;
        Button clearListButton = binding.clearListButton;
        TextView sumText = binding.sumText;
        TextView multText = binding.multText;
        TextView divideText = binding.divideText;

        addNumberButton.setOnClickListener(v -> {
            String input = integerInput.getText().toString().trim();
            if (!input.isEmpty()) {
                try {
                    int value = Integer.parseInt(input);
                    integerList.add(value);
                    integerInput.setText("");
                    updateNumberListUI(numberListContainer, this);
                    updateSumText(sumText);
                } catch (NumberFormatException ignored) {}
            }
        });

        multiplyNumberButton.setOnClickListener(v -> {
            String input = integerInput.getText().toString().trim();
            if (!input.isEmpty()) {
                try {
                    int value = Integer.parseInt(input);
                    integerList.add(value);
                    integerInput.setText("");
                    updateNumberListUI(numberListContainer, this);
                    updateMultiplyText(multText);
                } catch (NumberFormatException ignored) {}
            }
        });

        divideNumberButton.setOnClickListener(v -> {
            String input = integerInput.getText().toString().trim();
            if (!input.isEmpty()) {
                try {
                    int value = Integer.parseInt(input);
                    integerList.add(value);
                    integerInput.setText("");
                    updateNumberListUI(numberListContainer, this);
                    updateDivideText(divideText);
                } catch (NumberFormatException ignored) {}
            }
        });

        clearListButton.setOnClickListener(v -> {
            integerList.clear();
            updateNumberListUI(numberListContainer, this);
            updateSumText(sumText);
            updateMultiplyText(multText);
            updateDivideText(divideText);
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

    private void updateSumText(TextView sumText) {
        int sum = 0;
        sum = sumIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        sumText.setText("Sum: " + sum);
    }

    private void updateMultiplyText(TextView multText) {
        int prod = 0;
        prod = multiplyIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        multText.setText("Prod: " + prod);
    }

    private void updateDivideText(TextView divideText) {
        int result = 0;
        result = divideIntegerArrayList(integerList.stream().mapToInt(i -> i).toArray());
        divideText.setText("Div: " + result);
    }

    /**
     * A native method that is implemented by the 'ndklab' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int suma(int a, int b);

    public native int sumIntegerArrayList(int[] numbers);

    public native int multiply(int a, int b);

    public native int divide(int a, int b);

    public native int multiplyIntegerArrayList(int[] numbers);

    public native int divideIntegerArrayList(int[] numbers);

}