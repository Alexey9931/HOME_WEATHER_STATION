package com.example.homeweatherstationapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.example.homeweatherstationapp.databinding.DbTableFragmentBinding;
import com.github.mikephil.charting.charts.PieChart;

public class DBTableFragment extends Fragment {
    private DbTableFragmentBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        binding = DbTableFragmentBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        WebView browser=root.findViewById(R.id.DB_Table);
        browser.setInitialScale(100);
        browser.getSettings().setBuiltInZoomControls(true);
        browser.getSettings().setDisplayZoomControls(false);
        browser.loadUrl("http://alexgorlov99.ru/esp-data.php");

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}
