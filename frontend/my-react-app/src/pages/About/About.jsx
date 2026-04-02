import React from 'react';
import { useLanguage } from '../../context/LanguageContext';
import './About.css';
import photo1 from './photo1.jpg';
import photo2 from './photo2.jpg';

const About = () => {
  const { t } = useLanguage();

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
      <h1 className="about-title">{t('about.title')}</h1>
      <h2 className="about-description">{t('about.description')}</h2>
      <div className="team-cards">
        {teamMembers.map((member) => (
          <div key={member.id} className="team-card">
            <div className="card-photo">
              <img src={member.photo} alt={member.name} />
            </div>
            
            <div className="card-info">
              <h2 className="member-name">{member.name}</h2>
              <p className="member-education">{member.education}</p>
              <p className="member-position">{member.position}</p>
              <div className="member-goal">
                <h3>{t('about.learningObjective')}</h3>
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