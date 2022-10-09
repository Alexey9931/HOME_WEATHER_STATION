package com.example.homeweatherstationapp;

import android.os.Bundle;
import android.text.util.Linkify;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.databinding.FragmentMoreDetailsBinding;

import java.text.DecimalFormat;

public class MoreDetailsFragment extends Fragment {
    private FragmentMoreDetailsBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        binding = FragmentMoreDetailsBinding.inflate(inflater, container, false);
        View root = binding.getRoot();
        DecimalFormat decimalFormat = new DecimalFormat( "#.##" );
        CalculateDetails calculateDetails = new CalculateDetails();

        final TextView textView_avg_str_temp = root.findViewById(R.id.textView_avg_str_temp);
        final TextView textView_avg_home_temp = root.findViewById(R.id.textView_avg_home_temp);
        final TextView textView_avg_str_hum = root.findViewById(R.id.textView_avg_str_hum);
        final TextView textView_avg_home_hum = root.findViewById(R.id.textView_avg_home_hum);
        final TextView textView_avg_rainfall = root.findViewById(R.id.textView_avg_rainfall);
        final TextView textView_avg_wind_speed = root.findViewById(R.id.textView_avg_wind_speed);



        textView_avg_str_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST1)))) + "°C");
        textView_avg_home_temp.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST7)))) + "°C");
        textView_avg_str_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST2)))) + "%");
        textView_avg_home_hum.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST8)))) + "%");
        textView_avg_rainfall.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST3)))));
        textView_avg_wind_speed.setText(Float.toString(Float.parseFloat(decimalFormat.format(calculateDetails.CalculateAverage(Firebase.LIST6)))) + "м/с");

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}
