import React from 'react';
import './About.css';
import photo1 from './photo1.jpg'; 
import photo2 from './photo2.jpg';

const About = () => {
  const teamMembers = [
    {
      id: 1,
      name: 'Artem Mednov',
      education: 'Peter the Great St. Petersburg Polytechnic University',
      position: 'Frontend',
      learningGoal: 'Through this project, I will learn how to work with Git, React, and JavaScript. I will gain an understanding of how the frontend interacts with the backend and gain experience working as part of a team.',
      photo: photo1 
    },
    {
      id: 2,
      name: 'Roman Lednev',
      education: 'Saint Petersburg State University of Telecommunications (Bonch Bruevich)',
      position: 'Backend',
      learningGoal: 'Чему может научиться с помощью этого проекта',
      photo: photo2 
    }
  ];

  return (
    <div className="about-page">
      <h1 className="about-title">About Us</h1>
      <h2 className="about-description">This is a pet project by two students. Its goal is to create an online library that allows users to log in, read, and search for books. The homepage will feature book recommendations and include a search function that lets users filter books by various criteria—ideal for those who aren’t sure what to read. Bookhub will also remember where you left off and let you add bookmarks.</h2>
      
      <div className="team-cards">
        {teamMembers.map((member) => (
          <div key={member.id} className="team-card">
            <div className="card-photo">
              {member.photo ? (
                <img src={member.photo} alt={member.name} />
              ) : (
                <div className="photo-placeholder">
                  <span>Photo</span>
                </div>
              )}
            </div>
            
            <div className="card-info">
              <h2 className="member-name">{member.name}</h2>
              <p className="member-education">{member.education}</p>
              <p className="member-position">{member.position}</p>
              <div className="member-goal">
                <h3>learning objective:</h3>
                <p>{member.learningGoal}</p>
              </div>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default About;