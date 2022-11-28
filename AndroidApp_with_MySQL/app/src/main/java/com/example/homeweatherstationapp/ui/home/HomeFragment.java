package com.example.homeweatherstationapp.ui.home;

import android.app.AlertDialog;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.BackgroundWorker;
import com.example.homeweatherstationapp.EmailPasswordActivity;
import com.example.homeweatherstationapp.Firebase;
import com.example.homeweatherstationapp.R;
import com.example.homeweatherstationapp.databinding.FragmentHomeBinding;

import java.util.Date;
import java.util.List;

public class HomeFragment extends Fragment {

    private FragmentHomeBinding binding;
    public static ImageView imagewind;
    public static TextView STREET_TEMP;
    public static TextView STREET_HUM;
    public static TextView HOME_TEMP;
    public static TextView HOME_HUM;
    public static TextView RAIN;
    public static TextView VBat;
    public static TextView WIND_SPEED;
    public static TextView WIND_DIRECTION;
    public static TextView PRESSURE;
    public static TextView TIME;
    public static ImageView weath_forecast;

    public static String time_for_display = "";

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentHomeBinding.inflate(inflater, container, false);
        View root = binding.getRoot();
        //Firebase firebase = new Firebase();


        imagewind = root.findViewById(R.id.imagewind);
        STREET_TEMP = root.findViewById(R.id.STREET_TEMP);
        STREET_HUM = root.findViewById(R.id.STREET_HUM);
        HOME_TEMP = root.findViewById(R.id.HOME_TEMP);
        HOME_HUM = root.findViewById(R.id.HOME_HUM);
        RAIN = root.findViewById(R.id.RAIN);
        VBat = root.findViewById(R.id.VBat);
        WIND_SPEED = root.findViewById(R.id.WIND_SPEED);
        WIND_DIRECTION = root.findViewById(R.id.WIND_DIRECTION);
        PRESSURE = root.findViewById(R.id.PRESSURE);
        TIME = root.findViewById(R.id.TIME);
        weath_forecast = root.findViewById(R.id.imageView_weath_forecast);


        BackgroundWorker backgroundWorker = new BackgroundWorker(getContext());
        backgroundWorker.execute("http://alexgorlov99.ru/validateData1.php","login");


        //firebase.get_firebase(getContext(), STREET_TEMP, STREET_HUM, RAIN, VBat, WIND_SPEED, WIND_DIRECTION, HOME_TEMP, HOME_HUM, PRESSURE, TIME, imagewind, weath_forecast);

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

}