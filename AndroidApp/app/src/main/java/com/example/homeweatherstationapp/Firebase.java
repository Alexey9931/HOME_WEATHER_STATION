package com.example.homeweatherstationapp;

import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.GenericTypeIndicator;
import com.google.firebase.database.ValueEventListener;

import java.util.List;

public class Firebase {

    private FirebaseAuth mAuth;
    private DatabaseReference myRef;

    public static List<String> LIST1;
    public static List<String> LIST2;
    public static List<String> LIST3;
    public static List<String> LIST4;
    public static List<String> LIST5;
    public static List<String> LIST6;
    public static List<String> LIST7;
    public static List<String> LIST8;
    public static List<String> LIST9;

    public static String street_temp;
    public static String street_hum;
    public static String home_temp;
    public static String home_hum;
    public static String wind_speed;
    public static String wind_direct;
    public static String v_bat;
    public static String amount_rain;
    public static String pressure;

    public void get_firebase(TextView textView1, TextView textView2, TextView textView3,
                             TextView textView4, TextView textView5, TextView textView6, TextView textView7, TextView textView8, TextView textView9, ImageView imageview)
    {

        myRef = FirebaseDatabase.getInstance().getReference();
        FirebaseUser user = mAuth.getInstance().getCurrentUser();

        myRef.child(user.getUid()).addValueEventListener(new ValueEventListener() {

            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                GenericTypeIndicator<List<String>> t = new GenericTypeIndicator<List<String>>() {};
                LIST1 = dataSnapshot.child("DATA").child("STREET_TEMP").getValue(t);
                street_temp = LIST1.get(LIST1.size()-1);
                textView1.setText(street_temp);
                LIST2 = dataSnapshot.child("DATA").child("STREET_HUM").getValue(t);
                street_hum = LIST2.get(LIST2.size()-1);
                textView2.setText(street_hum + ".0");
                LIST3 = dataSnapshot.child("DATA").child("RAIN").getValue(t);
                amount_rain = LIST3.get(LIST3.size()-1);
                textView3.setText(amount_rain);
                LIST4 = dataSnapshot.child("DATA").child("VBAT").getValue(t);
                v_bat = LIST4.get(LIST4.size()-1);
                textView4.setText(v_bat);
                LIST5 = dataSnapshot.child("DATA").child("WIND_DIRECT").getValue(t);
                wind_direct = LIST5.get(LIST5.size()-1);
                textView6.setText(wind_direct);
                LIST6 = dataSnapshot.child("DATA").child("WIND_SPEED").getValue(t);
                wind_speed = LIST6.get(LIST6.size()-1);
                textView5.setText(wind_speed);
                LIST7 = dataSnapshot.child("DATA").child("HOME_TEMP").getValue(t);
                home_temp = LIST7.get(LIST7.size()-1);
                textView7.setText(home_temp);
                LIST8 = dataSnapshot.child("DATA").child("HOME_HUM").getValue(t);
                home_hum = LIST8.get(LIST8.size()-1);
                textView8.setText(home_hum + ".0");
                LIST9 = dataSnapshot.child("DATA").child("PRESSURE").getValue(t);
                pressure = LIST9.get(LIST9.size()-1);
                textView9.setText(pressure);
                switch (wind_direct)
                {
                    case "N-W": imageview.setImageResource(R.drawable.nw);
                        break;
                    case "N": imageview.setImageResource(R.drawable.n);
                        break;
                    case "S": imageview.setImageResource(R.drawable.s);
                        break;
                    case "E": imageview.setImageResource(R.drawable.e);
                        break;
                    case "W": imageview.setImageResource(R.drawable.w);
                        break;
                    case "N-E": imageview.setImageResource(R.drawable.ne);
                        break;
                    case "S-W": imageview.setImageResource(R.drawable.sw);
                        break;
                    case "S-E": imageview.setImageResource(R.drawable.se);
                        break;
                    default: imageview.setImageResource(R.drawable.def);
                        break;
                }

            }
            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }

}