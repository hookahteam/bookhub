import React, { useState } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { useLanguage } from '../../context/LanguageContext';
import './SignIn.css';

const SignIn = () => {
  const { t } = useLanguage();
  const navigate = useNavigate();
  
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
    setError(''); // Очищаем ошибку при вводе
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setError('');
    
    try {
      const response = await fetch('http://85.192.42.15:8000/api/users/login', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          email: formData.email,
          password: formData.password
        })
      });
      
      const data = await response.json();
      
      if (!response.ok) {
        throw new Error(data.message || 'Ошибка при входе');
      }
      
      // 🔑 Если сервер вернёт токен — сохраним его
      if (data.token) {
        localStorage.setItem('token', data.token);
      }
      
      // Перенаправляем на главную
      navigate('/');
      
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="signin-page">
      <div className="signin-container">
        <h1 className="signin-title">{t('signIn.title')}</h1>
        
        {error && <div className="error-message">{error}</div>}
        
        <form className="signin-form" onSubmit={handleSubmit}>
          {/* Email */}
          <div className="form-group">
            <label htmlFor="email" className="form-label">
              {t('signIn.email')}
            </label>
            <input
              type="email"
              id="email"
              name="email"
              value={formData.email}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signIn.emailPlaceholder')}
              required
            />
          </div>

          {/* Password */}
          <div className="form-group">
            <label htmlFor="password" className="form-label">
              {t('signIn.password')}
            </label>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              className="form-input"
              placeholder={t('signIn.passwordPlaceholder')}
              required
            />
          </div>

          {/* Forgot Password Link */}
          <div className="forgot-password">
            <Link to="/forgot-password" className="forgot-link">
              {t('signIn.forgotPassword')}
            </Link>
          </div>

          {/* Submit Button */}
          <button 
            type="submit" 
            className="signin-btn"
            disabled={loading}
          >
            {loading ? t('signIn.loading') : t('signIn.submit')}
          </button>
        </form>
        
        {/* Link to Sign Up */}
        <div className="signup-link">
          <span>{t('signIn.noAccount')}</span>
          <Link to="/sign-up" className="signup-link-btn">
            {t('signIn.signUp')}
          </Link>
        </div>
      </div>
    </div>
  );
};

export default SignIn;