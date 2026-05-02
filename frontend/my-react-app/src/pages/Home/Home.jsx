import React, { useEffect, useState } from 'react';
import { useLanguage } from '../../context/LanguageContext';
import './Home.css';

const Home = () => {
  const { t } = useLanguage();
  const [books, setBooks] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    fetchRandomBooks();
  }, []);

  const fetchRandomBooks = async () => {
    try {
      setLoading(true);
      const response = await fetch('http://85.192.42.15:8000/api/books');
      
      if (!response.ok) {
        throw new Error(`Ошибка: ${response.status}`);
      }
      
      const data = await response.json();
      setBooks(data.books);
      setError(null);
    } catch (err) {
      setError(err.message);
      console.error('Ошибка при получении книг:', err);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="home-page">
      <h1 className="home-title">{t('home.title')}</h1>
      
      {loading && <div className="loading">{t('home.loading')}</div>}
      {error && <div className="error">{t('home.error')}{error}</div>}
      {!loading && !error && books.length === 0 && (
        <div className="no-books">{t('home.noBooks')}</div>
      )}
      
      <div className="books-grid">
        {books.map((book) => (
          <div key={book.id} className="book-card">
            <h2 className="book-title">{book.title}</h2>
            <p className="book-author">{book.author}</p>
            <span className="book-id">ID: {book.id}</span>
            <span className="book-year">year: {book.year}</span>
          </div>
        ))}
      </div>
    </div>
  );
};

export default Home;