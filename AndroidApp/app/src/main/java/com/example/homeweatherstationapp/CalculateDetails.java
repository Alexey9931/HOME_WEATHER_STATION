package com.example.homeweatherstationapp;

import java.util.ArrayList;
import java.util.List;

public class CalculateDetails {

    public float CalculateAverage(List<String> LIST)
    {
        float Average = 0f;
        for(int i = 0; i < LIST.size(); i++)
        {
            Average += Float.parseFloat(LIST.get(i));
        }
        Average /= LIST.size();
        return Average;
    }
}
