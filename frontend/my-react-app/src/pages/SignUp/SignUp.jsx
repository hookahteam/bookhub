import React, { useState } from 'react';
import { useLanguage } from '../../context/LanguageContext';
import './SignUp.css';

const SignUp = () => {
  const { t } = useLanguage();
  
  const [formData, setFormData] = useState({
    username: '',
    email: '',
    password: '',
    confirmPassword: ''
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    const userData = {
      username: formData.username,
      email: formData.email,
      password: formData.password
    };
    
    try {
      const response = await fetch('http://85.192.42.15:8000/api/users/register', {
        method: 'POST', 
        headers: {
          'Content-Type': 'application/json' 
        },
        body: JSON.stringify(userData) 
      });
      
      if (!response.ok) {
        throw new Error(`Ошибка: ${response.status}`);
      }
      
      const result = await response.json();
      console.log('Успех:', result);
      
    } catch (error) {
      console.error('Ошибка при регистрации:', error);
    }
  };
  return (
    <div className="signup-page">
      <div className="signup-container">
        <h1 className="signup-title">{t('signUp.title')}</h1>
        
        <form className="signup-form" onSubmit={handleSubmit}>
          {/* Username */}
          <div className="form-group">
            <label htmlFor="username" className="form-label">
              {t('signUp.username')}
            </label>
            <input
              type="text"
              id="username"
              name="username"
              value={formData.username}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signUp.usernamePlaceholder')}
              required
            />
          </div>

          {/* Email */}
          <div className="form-group">
            <label htmlFor="email" className="form-label">
              {t('signUp.email')}
            </label>
            <input
              type="email"
              id="email"
              name="email"
              value={formData.email}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signUp.emailPlaceholder')}
              required
            />
          </div>

          {/* Password */}
          <div className="form-group">
            <label htmlFor="password" className="form-label">
              {t('signUp.password')}
            </label>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signUp.passwordPlaceholder')}
              required
              minLength={6}
            />
          </div>

          {/* Confirm Password */}
          <div className="form-group">
            <label htmlFor="confirmPassword" className="form-label">
              {t('signUp.confirmPassword')}
            </label>
            <input
              type="password"
              id="confirmPassword"
              name="confirmPassword"
              value={formData.confirmPassword}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signUp.confirmPasswordPlaceholder')}
              required
            />
          </div>

          {/* Submit Button */}
          <button type="submit" className="signup-btn">
            {t('signUp.submit')}
          </button>
        </form>
      </div>
    </div>
  );
};

export default SignUp;