package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.SpecialOffer;
import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class SpecialOfferDbRepo implements SpecialOfferRepository {
    private final String url, username, password;

    public SpecialOfferDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<SpecialOffer> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url ,username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from specialoffer")
        ) {
            List<SpecialOffer> specialOffers = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_offer");
                Long hotelId = resultSet.getLong("id_hotel");
                LocalDate startDate = resultSet.getDate("start_date").toLocalDate();
                LocalDate endDate = resultSet.getDate("end_date").toLocalDate();
                int percents = resultSet.getInt("percents");

                SpecialOffer specialOffer = new SpecialOffer(hotelId, startDate, endDate, percents);
                specialOffer.setId(id);

                specialOffers.add(specialOffer);
            }
            return specialOffers;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
