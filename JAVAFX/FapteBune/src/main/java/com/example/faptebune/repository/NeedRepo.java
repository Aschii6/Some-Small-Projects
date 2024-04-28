package com.example.faptebune.repository;

import com.example.faptebune.domain.Need;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class NeedRepo implements Repository<Long, Need> {
    private final String url, username, password;

    public NeedRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<Need> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from need")
        ){
            List<Need> needs = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_need");
                String title = resultSet.getString("title");
                String description = resultSet.getString("description");
                LocalDateTime deadline = resultSet.getTimestamp("deadline").toLocalDateTime();
                Long personInNeedId = resultSet.getLong("id_person_in_need");
                Long personHelpingId = resultSet.getLong("id_person_helping");
                String status = resultSet.getString("status");

                Need need = new Need(title, description, deadline, personInNeedId, status);
                need.setPersonHelpingId(personHelpingId);
                need.setId(id);

                needs.add(need);
            }
            return needs;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void update(Long needId, Long personHelpingId) {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("update need set " +
                        "id_person_helping = ?, status = 'Erou gasit!' where id_need = ?")
        ){
            preparedStatement.setLong(1, personHelpingId);
            preparedStatement.setLong(2, needId);

            int affectedRows = preparedStatement.executeUpdate();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
