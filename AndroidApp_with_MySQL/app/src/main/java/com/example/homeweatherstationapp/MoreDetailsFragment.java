package com.example.homeweatherstationapp;

import android.graphics.Color;
import android.os.Bundle;
import android.text.util.Linkify;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.databinding.FragmentMoreDetailsBinding;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.components.Description;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class MoreDetailsFragment extends Fragment {
    private FragmentMoreDetailsBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        binding = FragmentMoreDetailsBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        final PieChart WindDirectDiagram = root.findViewById(R.id.WindDirectDiagram);
        WindDirectDiagram.setVisibility(View.INVISIBLE);

        BackgroundWorker backgroundWorker = new BackgroundWorker(getContext());
        backgroundWorker.execute(   "http://alexgorlov99.ru/validateData-1day.php",
                "http://alexgorlov99.ru/validateData-3days.php",
                "http://alexgorlov99.ru/validateData-5days.php",
                "http://alexgorlov99.ru/validateData-7days.php","login");

        BackgroundWorkerForDetails backgroundWorkerForDetails = new BackgroundWorkerForDetails(getContext());
        backgroundWorkerForDetails.execute( root.findViewById(R.id.textView_avg_str_temp),root.findViewById(R.id.textView_avg_home_temp),
                                            root.findViewById(R.id.textView_avg_str_hum), root.findViewById(R.id.textView_avg_home_hum),
                                            root.findViewById(R.id.textView_avg_rainfall),root.findViewById(R.id.textView_avg_wind_speed),
                                            root.findViewById(R.id.textView_max_str_temp),root.findViewById(R.id.textView_max_home_temp),
                                            root.findViewById(R.id.textView_max_str_hum), root.findViewById(R.id.textView_max_home_hum),
                                            root.findViewById(R.id.textView_max_rainfall),root.findViewById(R.id.textView_max_wind_speed),
                                            root.findViewById(R.id.textView_max_bat_charge),root.findViewById(R.id.textView_min_str_temp),
                                            root.findViewById(R.id.textView_min_home_temp), root.findViewById(R.id.textView_min_str_hum),
                                            root.findViewById(R.id.textView_min_home_hum),root.findViewById(R.id.textView_min_rainfall),
                                            root.findViewById(R.id.textView_min_wind_speed),root.findViewById(R.id.textView_min_bat_charge),
                                            root.findViewById(R.id.WindDirectDiagram),root.findViewById(R.id.textView_start_time),
                                            root.findViewById(R.id.textView_end_time),root.findViewById(R.id.textView_number_mesuamer));



        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}
