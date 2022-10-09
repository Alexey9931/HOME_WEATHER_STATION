package com.example.homeweatherstationapp.ui.home;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import com.example.homeweatherstationapp.Firebase;
import com.example.homeweatherstationapp.R;
import com.example.homeweatherstationapp.databinding.FragmentHomeBinding;

import java.util.Date;

public class HomeFragment extends Fragment {

    private FragmentHomeBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentHomeBinding.inflate(inflater, container, false);
        View root = binding.getRoot();
        Firebase firebase = new Firebase();


        final ImageView imagewind = root.findViewById(R.id.imagewind);
        final TextView STREET_TEMP = root.findViewById(R.id.STREET_TEMP);
        final TextView STREET_HUM = root.findViewById(R.id.STREET_HUM);
        final TextView HOME_TEMP = root.findViewById(R.id.HOME_TEMP);
        final TextView HOME_HUM = root.findViewById(R.id.HOME_HUM);
        final TextView RAIN = root.findViewById(R.id.RAIN);
        final TextView VBat = root.findViewById(R.id.VBat);
        final TextView WIND_SPEED = root.findViewById(R.id.WIND_SPEED);
        final TextView WIND_DIRECTION = root.findViewById(R.id.WIND_DIRECTION);
        final TextView PRESSURE = root.findViewById(R.id.PRESSURE);
        final TextView TIME = root.findViewById(R.id.TIME);
        final ImageView weath_forecast = root.findViewById(R.id.imageView_weath_forecast);

        firebase.get_firebase(STREET_TEMP, STREET_HUM, RAIN, VBat, WIND_SPEED, WIND_DIRECTION, HOME_TEMP, HOME_HUM, PRESSURE, TIME, imagewind, weath_forecast);

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

}